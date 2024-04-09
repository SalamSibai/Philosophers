/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:41:20 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 18:03:54 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_share_data(t_shared_data *shared_data, int mutex_sn)
{
	if (mutex_sn >= 1)
	{
		if (pthread_mutex_destroy(shared_data->state_mutex))
			error_msg("failed to destroy state mutex\n");
	}
	if (mutex_sn >= 2)
	{
		if (pthread_mutex_destroy(shared_data->print_mutex))
			error_msg("failed to destroy print mutex\n");
	}
	if (mutex_sn >= 3)
	{
		if (pthread_mutex_destroy(shared_data->full_mutex))
			error_msg("faild to destroy full mutex\n");
	}
	free(shared_data->state_mutex);
	free(shared_data->print_mutex);
	free(shared_data->full_mutex);
	free(shared_data);
}

void	clean_forks(t_fork **forks, int index, bool end)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		if (!end)
		{
			if (i > 0)
			{
				pthread_mutex_destroy(forks[i - 1]->mutex);
				free(forks[i - 1]->mutex);
			}
		}
		else
		{
			pthread_mutex_destroy(forks[i]->mutex);
			free(forks[i]->mutex);
		}
		free(forks[i]);
	}
	free(forks);
}

void	clean_philos(t_philo **philos, int index, bool end)
{
	int	i;

	i = -1;
	if (index == -1)
		return;
	else
	{
		while (++i < index)
		{
			free(philos[i]);
			if (!end)
			{
				if (i > 0)
				
					free(philos[i - 1]->thread);
			}
			else
				free(philos[i]->thread);
		}
	}
	free(philos);
}

void	cleanup(t_philo **philo, t_fork **fork, t_shared_data *shared)
{
	clean_share_data(shared, 3);
	clean_forks(fork, shared->input->forks_num, true);
	clean_philos(philo, shared->input->philo_num, true);
}
