/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:53:58 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/08 14:13:53 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check if it has been longer than death_time 
 * 		since the last mealtime
 * @param philo philo reference
 * @return true if a philo should die
 * @return false if a philo should live
 */
bool should_die(t_philo *philo)
{
	struct timeval	tval;
	t_time_data		time_data;

	gettimeofday(&tval, NULL);
	time_data.curent = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
	time_data.last_meal = time_data.curent - philo->last_mealtime
		- philo->shared_data->simulation_start_time;
	if(time_data.last_meal > philo->shared_data->input->death_timer
		&& philo->last_mealtime != 0)
	{
		// pthread_mutex_lock(philo->shared_data->state_mutex);
		// if (philo->shared_data->all_alive == false)
		// 	pthread_mutex_unlock(philo->shared_data->state_mutex);
		// else
		// {
			philo->shared_data->all_alive = false;
			//pthread_mutex_unlock(philo->shared_data->state_mutex);
			philo->state = DEAD;
			time_data.print =
				time_data.curent - philo->shared_data->simulation_start_time;
			printf("death time: %ld\n", time_data.print);
			philo->death_time = time_data.print;
			print_dead(philo);
		//}
		return (true);
	}
	return (false);
}