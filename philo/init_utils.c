/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:21:14 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:21:17 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_utils(t_philo **philo, t_fork **fork, t_input *input, int i)
{
	if (i == 0)
		philo[i]->l_fork = fork[input->forks_num - 1];
	else
		philo[i]->l_fork = fork[i - 1];
	philo[i]->r_fork = fork[i];
	philo[i]->meal_ctr = 0;
	philo[i]->death_time = -1;
	philo[i]->last_mealtime = 0;
	philo[i]->count_meals = false;
}

void	init_forks_utils(t_fork *fork, int i)
{
	fork->sn = i + 1;
	fork->in_use = false;
	fork->last_user = -1;
}
