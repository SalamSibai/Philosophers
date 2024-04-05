/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:40 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/03 23:36:38 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dream(t_philo *philo, time_t total_sleep_time)
{
	time_t	sleep_time;
	time_t	sleep_start;
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	sleep_start = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
	sleep_time = sleep_start;
	while ((sleep_time - sleep_start < total_sleep_time))
	{
		if (gonna_die(philo))
			return (false);
		else
		{
			pthread_mutex_lock(&philo->data->state_mutex);
			if (philo->data->all_alive)
			{
				pthread_mutex_unlock(&philo->data->state_mutex);
				usleep(100);
			}
			else
			{
				pthread_mutex_unlock(&philo->data->state_mutex);
				return (false);
			}
			gettimeofday(&tval, NULL);
			sleep_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		}
	}
	return (true);
}


bool	philo_sleep(t_philo *philo)
{
	struct timeval	tval;
	time_t			sleep_start_time;
	time_t			think_start_time;
	time_t			print_time;

	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		gettimeofday(&tval, NULL);
		sleep_start_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000); //everything is in milliseconds
		print_time = sleep_start_time - philo->data->start_time;
		print_sfly(philo, "is sleeping", print_time);
		if(!dream(philo, (philo->data->sleep_timer)))
			return (false);
		gettimeofday(&tval, NULL);
		think_start_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		print_time = think_start_time - philo->data->start_time;
		print_sfly(philo, "is thinking", print_time);
	}
	else
		pthread_mutex_unlock(&philo->data->state_mutex);
	return (true);
}
