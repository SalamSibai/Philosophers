/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:52:31 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:00:01 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_meals_eaten(t_philo *philo)
{
	philo->meal_ctr ++;
	if (philo->meal_ctr == philo->shared_data->input->food_ctr)
	{
		pthread_mutex_lock(philo->shared_data->full_mutex);
		philo->shared_data->full_ctr ++;
		pthread_mutex_unlock(philo->shared_data->full_mutex);
	}
}

bool	use_forks(t_philo *philo)
{
	philo->r_fork->in_use = 1;
	philo->l_fork->in_use = 1;
	philo->r_fork->last_user = philo->sn;
	philo->l_fork->last_user = philo->sn;
	leave_forks(philo);
	return (true);
}
