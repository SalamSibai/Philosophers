/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:46:11 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/03 23:35:55 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_sfly(t_philo *philo, char *msg, long timestamp)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("time: %ld | Philosopher %d %s\n", timestamp ,philo->sn, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/// @brief creates the philosophers
/// @param philo philosophers reference
/// @param data data reference
/// @return returns 1 if creation for all was successful
int	make_philosophers(t_philo **philo, t_data *data)
{
	int		i;

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
	i = -1;
	while (++i < data->philo_num)
	{
		if (philo[i]->autopsy_report.death_time > 0)
		{
			print_sfly(philo[i], "is dead", philo[i]->autopsy_report.death_time);
			break;
		}
	}
	return (1);
}

// * ./philo 1 800 200 200: Should not eat and die
// * ./philo 5 800 200 200 7: No one should die
// * ./philo 4 410 200 200: No one should die
// * ./philo 4 310 200 100: A philosopher should die
// * ./philo 3 1000 500 600  A philosopher should die
// * ./philo 5 200 100 60  A philosopher should die
// * ./philo 4 500 400 300  A philosopher should die
// * ./philo 3 700 200 200 Philosophers shouldnt die here
// * ./philo 2 200 200 100  A philosopher should die
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