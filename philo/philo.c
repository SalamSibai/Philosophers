/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:28:22 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 18:03:12 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philosophers(t_philo **philos, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->philo_num)
	{
		pthread_create(philos[i]->thread, NULL, (void *)&start_sim, philos[i]);
		usleep(350);
	}
	i = -1;
	while (++i < input->philo_num)
		pthread_join(*philos[i]->thread, NULL);
	return (1);
}


int philo(t_input *input)
{
	t_philo			**philos;
	t_fork			**forks;
	t_shared_data	*shared_data;

	philos = NULL;
	forks = NULL;
	shared_data = NULL;
	shared_data = malloc(sizeof(t_shared_data));
	if (!shared_data)
		return (error_msg("No space for shared data"), 0);
	if (!init_shared_data(shared_data, input))
		return (error_msg("No space for shared data"), 0);
	forks = malloc(sizeof(t_fork *) * (input->forks_num + 1));
	if (!forks)
		return (error_msg("No space for forks"), 0);
	if (!init_forks(forks, input))
		return (0); //print error msg firs (NO SPACE for forks)
	philos = malloc(sizeof(t_philo *) * (input->philo_num + 1));
	if (!philos)
		return (0); //print error msg firs (NO SPACE for philos)
	if (!init_philos(philos, forks, input, shared_data))
		return (0); //print error msg firs (NO SPACE for philos)
	make_philosophers(philos, input);
	cleanup(philos, forks, shared_data);
	return (1);
}