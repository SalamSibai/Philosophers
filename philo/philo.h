/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 20:47:46 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "../parsing/parsing.h"

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}	t_state;


typedef struct s_data
{
	time_t	start_time;
	int		philo_num;
	int		forks;
	int		death_timer;
	int		food_timer;
	int		sleep_timer;
	int		food_ctr;
}	t_data;

/// @brief					the philosophers struct
/// @param	state			the state the philosopher is in
/// @param	sn				the philosopher's serial number
/// @param	last_mealtime	last time the philosopher had something to eat
typedef struct s_philo
{
	t_state			state;
	unsigned int	sn;
	unsigned int	meal_ctr;
	time_t			last_mealtime;	


} t_philo;



void	error_handler(char *msg, int cleanup);
void	data_init(t_data *data, char **nums);

#endif