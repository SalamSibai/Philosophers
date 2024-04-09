/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:01:18 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief changes the order of locking the fork mutex
 * 
 * @param philo philo reference
 * @param left if true, lock left first
 */
bool	grab_forks(t_philo *philo)
{
	if (philo->sn == philo->shared_data->input->philo_num)
	{
		if (philo->r_fork != philo->l_fork)
		{
			pthread_mutex_lock(philo->r_fork->mutex);
			pthread_mutex_lock(philo->l_fork->mutex);
			return (true);
		}
	}
	else
	{
		if (philo->r_fork != philo->l_fork)
		{
			pthread_mutex_lock(philo->l_fork->mutex);
			pthread_mutex_lock(philo->r_fork->mutex);
			return (true);
		}
	}
	return (false);
}

/**
 * @brief lets go of forks
 * 
 * @param philo philo reference
 */
void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork->mutex);
	pthread_mutex_unlock(philo->r_fork->mutex);
}

/**
 * @brief confirms if both forks can be taken
 * 
 * @param philo philo reference
 * @return true if both forks can be taken 
 * @return false if one or neither forks cant be taken
 */
bool	take_forks(t_philo *philo)
{
	bool	l_available;
	bool	r_available;

	l_available = true;
	r_available = true;
	if (!philo->r_fork->in_use && !philo->l_fork->in_use)
	{
		if (philo->r_fork->last_user != 0)
		{
			if (philo->r_fork->last_user != philo->sn)
				r_available = true;
			else
				r_available = false;
		}
		if (philo->l_fork->last_user != 0)
		{
			if (philo->l_fork->last_user != philo->sn)
				l_available = true;
			else
				l_available = false;
		}
		return (r_available && l_available);
	}
	return (false);
}

/**
 * @brief the eating state of a philosopher
 * 
 * @param philo philo reference
 * @return true if a philosopher finished eating
 * @return false if a philosopher died while eating,
 * 			or someone else died
 */
bool	philo_eat(t_philo	*philo)
{
	struct timeval	tval;
	t_time_data		time_data;

	pthread_mutex_lock(philo->shared_data->state_mutex);
	if (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(philo->shared_data->state_mutex);
		gettimeofday(&tval, NULL);
		time_data.last_meal
			= (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
		time_data.print
			= time_data.last_meal - philo->shared_data->simulation_start_time;
		philo->last_mealtime = time_data.print;
		print_eating(philo);
		if (philo->count_meals == true)
			increment_meals_eaten(philo);
		if (!doing(philo, (philo->shared_data->input->food_timer)))
			return (false);
		grab_forks(philo);
		philo->l_fork->in_use = 0;
		philo->r_fork->in_use = 0;
		leave_forks(philo);
		return (true);
	}
	return (pthread_mutex_unlock(philo->shared_data->state_mutex), false);
}

/**
 * @brief main thread loop. looks for forks
 * 
 * @param philo philo reference
 * @return void* if NULL, someone died
 */
bool	find_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data->state_mutex);
	while (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(philo->shared_data->state_mutex);
		if (should_die(philo))
			return (false);
		if (!grab_forks(philo))
		{
			usleep(100);
			pthread_mutex_lock(philo->shared_data->state_mutex);
			continue ;
		}
		if (take_forks(philo))
			return (use_forks(philo));
		else
			leave_forks(philo);
		usleep(100);
		pthread_mutex_lock(philo->shared_data->state_mutex);
	}
	pthread_mutex_unlock(philo->shared_data->state_mutex);
	return (false);
}
