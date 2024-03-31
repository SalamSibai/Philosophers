/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:16:40 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/31 23:46:14 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
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
		printf("time: %ld | Philosopher %d is sleeping\n", print_time, philo->sn);
		usleep((philo->data->sleep_timer) * 1000);
		gettimeofday(&tval, NULL);
		think_start_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		print_time = think_start_time - philo->data->start_time;
		printf("time: %ld | Philosopher %d is thinking\n", print_time, philo->sn);
	}
	else
		pthread_mutex_unlock(&philo->data->state_mutex);
}
