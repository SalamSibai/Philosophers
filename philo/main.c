/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:48:05 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 18:08:29 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_data *data, char **nums)
{
	data->philo_num = ft_atol(nums[0]);
	if (data->philo_num == -1)
		printf("error\n");
	data->forks = data->philo_num;
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
		data->food_ctr = 0;
	
	printf("%d\n", data->food_ctr);
}

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
	return (0);
}