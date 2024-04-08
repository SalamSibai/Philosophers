/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:09:05 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/08 13:09:07 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_sleep(t_philo *philo)
{
	struct timeval	tval;
	t_time_data		time_data;

	pthread_mutex_lock(philo->shared_data->state_mutex);
	if (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(philo->shared_data->state_mutex);
		gettimeofday(&tval, NULL);
		time_data.curent = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		time_data.print = 
			time_data.curent - philo->shared_data->simulation_start_time;
		print_sleeping(philo, time_data.print);
		if (!doing(philo, philo->shared_data->input->sleep_timer))
			return (false);
		gettimeofday(&tval, NULL);
		time_data.curent = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		time_data.print =
			time_data.curent - philo->shared_data->simulation_start_time;
		print_thinking(philo, time_data.print);
		return (true);
	}
	pthread_mutex_unlock(philo->shared_data->state_mutex);
	return (false);
}