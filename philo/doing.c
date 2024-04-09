/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:29:42 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 20:50:32 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	doing(t_philo *philo, time_t time_it_takes)
{
	struct timeval	tval;
	t_time_data		time_data;

	gettimeofday(&tval, NULL);
	time_data.start_doing = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
	time_data.doing_elapsed = time_data.start_doing;
	while ((time_data.doing_elapsed - time_data.start_doing < time_it_takes))
	{
		if (should_die(philo))
			return (false);
		else
		{
			usleep(100);
			gettimeofday(&tval, NULL);
			time_data.doing_elapsed
				= (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
		}
	}
	return (true);
}
