/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:07:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:20:00 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief initializes the input struct
 * 
 * @param input input reference
 * @param nums nums 2d array
 */
bool	init_input(t_input *input, char **nums)
{
	input->philo_num = ft_atol(nums[0]);
	if (input->philo_num == -1)
		return (error_msg("wrong value for philos"), false);
	input->forks_num = input->philo_num;
	input->death_timer = ft_atol(nums[1]);
	if (input->death_timer == -1)
		return (error_msg("wrong value for death timer"), false);
	input->food_timer = ft_atol(nums[2]);
	if (input->food_timer == -1)
		return (error_msg("wrong value for food timer"), false);
	input->sleep_timer = ft_atol(nums[3]);
	if (input->sleep_timer == -1)
		return (error_msg("wrong value for sleep timer"), false);
	if (tot_vars(nums) == 5)
	{
		input->food_ctr = ft_atol(nums[4]);
		if (input->food_ctr == -1)
			return (error_msg("wrong value for food counter"), false);
	}
	else
		input->food_ctr = -1;
	free_matrix(nums);
	return (true);
}

/**
 * @brief initializes shared data struct
 * 
 * @param shared shared_data reference
 * @param input input reference
 * @return int 	if 1, success
 * 				if 0, failed
 */
bool	init_shared_data(t_shared_data *shared, t_input	*input)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	shared->simulation_start_time
		= (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
	shared->all_alive = true;
	shared->state_mutex = malloc(sizeof(pthread_mutex_t));
	if (!shared->state_mutex)
		return (false);
	shared->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!shared->print_mutex)
		return (free (shared->state_mutex), false);
	shared->full_mutex = malloc(sizeof(pthread_mutex_t));
	if (!shared->full_mutex)
		return (free(shared->state_mutex), free(shared->print_mutex), NULL);
	if (pthread_mutex_init((shared->state_mutex), NULL))
		return (clean_share_data(shared, 0), false);
	if (pthread_mutex_init((shared->print_mutex), NULL))
		return (clean_share_data(shared, 1), false);
	if (pthread_mutex_init((shared->full_mutex), NULL))
		return (clean_share_data(shared, 2), false);
	shared->full_ctr = 0;
	shared->input = input;
	return (true);
}

/**
 * @brief initializes the forks struct
 * 
 * @param forks reference to forks pointer
 * @param input reference to input
 * @return int 	the index that we free to
 * 				if 1, succeeds
 * 				if 0, fails
 */
bool	init_forks(t_fork **forks, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->forks_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
		{
			if (i == 0)
				return (false);
			return (clean_forks(forks, i, false), false);
		}
		forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		if (!forks[i]->mutex)
			return (clean_forks(forks, i, false), false);
		if (pthread_mutex_init((forks[i]->mutex), NULL))
		{
			free(forks[i]->mutex);
			return (clean_forks(forks, i, false), false);
		}
		init_forks_utils(forks[i], i);
	}
	forks[i] = NULL;
	return (true);
}

/**
 * @brief initializes the philosophers struct
 * 
 * @param philo reference to philo pointer
 * @param fork reference to forks pointer
 * @param input reference to input
 * @param shared reference to shared data
 * @return int 	the index that we free till
 * 				if 1, succeeds
 * 				if 0, fails
 */
bool	init_philos(t_philo **phi, t_fork **f, t_input *in, t_shared_data *srd)
{
	int	i;

	i = -1;
	while (++i < in->philo_num)
	{
		phi[i] = malloc(sizeof(t_philo));
		if (!phi[i])
		{
			if (i == 0)
				return (clean_philos(phi, -1, false), false);
			return (clean_philos(phi, i, false), false);
		}
		phi[i]->thread = malloc(sizeof(pthread_t));
		if (!phi[i]->thread)
			return (clean_philos(phi, i, false), NULL);
		phi[i]->sn = i + 1;
		phi[i]->shared_data = srd;
		init_philo_utils(phi, f, in, i);
		if (in->food_ctr > 0)
			phi[i]->count_meals = true;
	}
	phi[i] = NULL;
	return (1);
}
