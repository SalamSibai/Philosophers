/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:46:11 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/31 23:05:04 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief creates the philosophers
/// @param philo philosophers reference
/// @param data data reference
/// @return returns 1 if creation for all was successful
int	make_philosophers(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_create(philo[i]->thread, NULL, (void *)&check_forks, philo[i]);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		pthread_join(*philo[i]->thread, NULL);
	}
	return (1);
}

int	philo(t_data *data)
{
	t_philo	**philos;
	t_fork	**forks;

	philos = malloc(sizeof(t_philo *) * (data->philo_num + 1));
	if (!philos)
		printf("NO SPACE FREE PLEASE\n");
	forks = malloc(sizeof(t_fork *) * (data->forks_num + 1));
	if (!forks)
		printf("NO SPACE FREE PLEASE\n");
	if (!fork_init(forks, data))
		printf("NO SPACE FREE PLEASE\n");
	if (!philo_init(philos, data, forks))
		printf("NO SPACE FREE PLEASE\n");
	make_philosophers(philos, data);
	
	//if (!make_forks(forks, data))
	return (1);
	//create the threads here
	//create the mutexes here
}