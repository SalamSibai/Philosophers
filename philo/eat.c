/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:50 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/08 13:55:46 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief changes the order of locking the fork mutex
 * 
 * @param philo philo reference
 * @param left if true, lock left first
 */
void	grab_forks(t_philo  *philo, bool left)
{
	if (left)
	{
		pthread_mutex_lock(philo->r_fork->mutex);
		pthread_mutex_lock(philo->l_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork->mutex);
		pthread_mutex_lock(philo->r_fork->mutex);
	}
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
	if (!philo->r_fork->in_use && !philo->l_fork->in_use
		&& philo->l_fork != philo->r_fork)
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
		time_data.last_meal = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		time_data.print =
			time_data.last_meal - philo->shared_data->simulation_start_time;
		philo->last_mealtime = time_data.print;
		philo->r_fork->last_user = philo->sn;
		philo->l_fork->last_user = philo->sn;
		print_eating(philo);
		if (philo->count_meals == true)
			philo->meal_ctr ++;
		if(!doing(philo, (philo->shared_data->input->food_timer)))
			return (false);
		if (philo->sn == philo->shared_data->input->philo_num)
			grab_forks(philo, true);
		else
			grab_forks(philo, false);
		philo->l_fork->in_use = 0;
		philo->r_fork->in_use = 0;
		leave_forks(philo);
		return (true);
		//if (!philo_sleep(philo))
		// 	return (false);
	}
	pthread_mutex_unlock(philo->shared_data->state_mutex);
	return (false);
	//return (true);
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
		if (philo->sn == philo->shared_data->input->philo_num)
			grab_forks(philo, true);
		else
			grab_forks(philo, false);
		if (take_forks(philo))
		{
			philo->r_fork->in_use = 1;
			philo->l_fork->in_use = 1;
			leave_forks(philo);
			//philo_eat(philo);
			return (true);
		}
		else
			leave_forks(philo);
		pthread_mutex_lock(philo->shared_data->state_mutex);
		usleep(100);
	}
	pthread_mutex_unlock(philo->shared_data->state_mutex);
	return (false);
}
