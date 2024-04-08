/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:53:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/08 14:15:56 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_sim(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data->state_mutex);
	while (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(philo->shared_data->state_mutex);
		if (should_die(philo))
			return (NULL);
		if (!find_forks(philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		pthread_mutex_lock(philo->shared_data->state_mutex);
		usleep(100);
	}
	pthread_mutex_unlock(philo->shared_data->state_mutex);
	return (NULL);
}
