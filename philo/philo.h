/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 17:53:57 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../parsing/parsing.h"

typedef struct s_data
{
	int	philo_num;
	int	forks;
	int	death_timer;
	int	food_timer;
	int	sleep_timer;
	int	food_ctr;
}	t_data;

void	error_handler(char *msg, int cleanup);

#endif