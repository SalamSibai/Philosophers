/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:48:05 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 20:45:36 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	char	**nums;

	nums = validate(ac-1, av);
	if (!nums)
		return (0);
	data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	data_init(data, nums);
	printf("num of philos is %d\n", data->philo_num);
	printf("num of forks is %d\n", data->forks);
	printf("death timer is %d\n", data->death_timer);
	printf("food timer is %d\n", data->food_timer);
	printf("sleep timer is %d\n", data->sleep_timer);
	printf("food ctr is %d\n", data->food_ctr);
	return (0);
}