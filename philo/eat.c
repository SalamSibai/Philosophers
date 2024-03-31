/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:10:07 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/01 00:07:38 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	struct timeval	tval;
	time_t			eat_start_time;
	time_t			print_time;

	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		gettimeofday(&tval, NULL);
		eat_start_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000); //everything is in milliseconds
		print_time = eat_start_time - philo->data->start_time;
		philo->last_mealtime = print_time;
		printf("time: %ld | Philosopher %d is eating\n", print_time, philo->sn);
		usleep((philo->data->food_timer) * 1000);
		pthread_mutex_lock(&philo->l_fork->mutex);
		pthread_mutex_lock(&philo->r_fork->mutex);
		philo->l_fork->in_use = 0;
		philo->r_fork->in_use = 0;
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		philo_sleep(philo);
	}
	else
		pthread_mutex_unlock(&philo->data->state_mutex);
}

/// @brief check if the specific fork is in use or not
/// @param philo the philosopher checking
void	*check_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	while (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		if (gonna_die(philo))
			return (NULL);
		pthread_mutex_lock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->l_fork->mutex);
		if ((!philo->r_fork->in_use) && (!philo->l_fork->in_use))
		{
			philo->r_fork->in_use = 1;
			philo->l_fork->in_use = 1;
			pthread_mutex_unlock(&philo->l_fork->mutex);
			pthread_mutex_unlock(&philo->r_fork->mutex);
			philo_eat(philo);
		}
		else
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			pthread_mutex_unlock(&philo->r_fork->mutex);
		}
		pthread_mutex_lock(&philo->data->state_mutex);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (NULL);
}
