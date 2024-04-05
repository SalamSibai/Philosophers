/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:18:22 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/03 22:34:20 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_philo.h"

/// @brief might die dunno
/// @param philo 
/// @return will die or nah
bool	gonna_die(t_philo *philo)
{
	struct timeval	tval;
	time_t	current_time;
	time_t	print_time;

	gettimeofday(&tval, NULL);
	current_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
	if (current_time - philo->last_mealtime - philo->data->start_time > philo->data->death_timer
		&& philo->last_mealtime != 0)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->all_alive)
			philo->data->all_alive = false;
		else
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
		print_time = current_time - philo->data->start_time;
		philo->autopsy_report.death_time = print_time;
		//printf("time: %ld | Philosopher %d is dead\n", print_time, philo->sn);
		return (true);
	}
	return (false);
}
