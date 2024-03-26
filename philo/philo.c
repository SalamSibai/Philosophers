/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:46:11 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/26 22:16:05 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/// @brief creates the forks
/// @param fork forks reference
/// @param data data reference
/// @return returns 1 if creation of all was successful
int	make_forks(t_fork **fork, t_data *data)
{
	
}

/// @brief creates the philosophers
/// @param philo philosophers reference
/// @param data data reference
/// @return returns 1 if creation for all was successful
int	make_philosophers(t_philo **philo, t_fork **fork, t_data *data)
{
	(void) fork;
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			printf("PROBLEM PLS FREE\n");
				return (0);
		}
		philo[i]->sn = i;
		
	}
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
	
	//if (!make_forks(forks, data))
		
	//make_philosophers(philos, fork, data);
	return (1);
	//create the threads here
	//create the mutexes here
}