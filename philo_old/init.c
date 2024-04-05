/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:39:54 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/03 23:31:25 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "old_philo.h"

void	data_init(t_data *data, char **nums)
{
	struct timeval	tval;

	data->all_alive = true;
	if (pthread_mutex_init(&(data->state_mutex), NULL))
		printf("error\n");
	if (pthread_mutex_init(&(data->print_mutex), NULL))
		printf("error\n");
	data->philo_num = ft_atol(nums[0]);
	if (data->philo_num == -1)
		printf("error\n");
	data->forks_num = data->philo_num;
	data->death_timer = ft_atol(nums[1]);
	if (data->death_timer == -1)
		printf("error\n");
	data->food_timer = ft_atol(nums[2]);
	if (data->food_timer == -1)
		printf("error\n");
	data->sleep_timer = ft_atol(nums[3]);
	if (data->sleep_timer == -1)
		printf("error\n");
	if (tot_vars(nums) == 5)
	{
		data->food_ctr = ft_atol(nums[4]);
		if (data->food_ctr == -1)
			printf("error\n");
	}
	else
		data->food_ctr = -1;
	gettimeofday(&tval, NULL);
	data->start_time = (tval.tv_sec * 1000) + (tval.tv_usec/1000); //everything is in milliseconds
}

int	fork_init(t_fork **forks, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->forks_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (0); //also free;
		forks[i]->sn = i;
		forks[i]->in_use = 0;
		if (pthread_mutex_init(&(forks[i]->mutex), NULL))
			return (0); //also free stuff
	}
	forks[i] = NULL;
	return (1);
}

int	philo_init(t_philo **philo, t_data *data, t_fork **fork)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (0); //pls free
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (!philo[i]->thread)
			return (0); //pls free
		philo[i]->sn = i + 1;
		philo[i]->state = ALIVE;
		philo[i]->meal_ctr = 0;
		philo[i]->last_mealtime = 0;
		if (i == 0)
			philo[i]->l_fork = fork[data->forks_num - 1];
		else
			philo[i]->l_fork = fork[i - 1];
		philo[i]->r_fork = fork[i];
		philo[i]->data = data;
		memset(&philo[i]->autopsy_report, 0, sizeof(t_autopsy_results));
	}
	philo[i] = NULL;
	return (1);
}