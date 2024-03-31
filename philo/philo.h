/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:53:48 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/31 23:37:35 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "../parsing/parsing.h"

typedef enum e_state
{
	ALIVE,
	DEAD
}	t_state;

typedef struct s_data
{
	bool	all_alive;
	time_t	start_time;
	pthread_mutex_t	state_mutex;
	int		philo_num;
	int		forks_num;
	int		death_timer;
	int		food_timer;
	int		sleep_timer;
	int		food_ctr;
}	t_data;

/// @brief the fork struct
/// @param sn the serial number
/// @param mutex the fork mutex
typedef struct s_fork
{
	int				sn;
	bool			in_use;
	pthread_mutex_t	mutex;
} t_fork;

/// @brief					the philosophers struct
/// @param	philo_thrd		the thread variable
/// @param	state			the state the philosopher is in
/// @param	sn				the philosopher's serial number
/// @param	last_mealtime	last time the philosopher had something to eat
typedef struct s_philo
{
	pthread_t		*thread;
	t_state			state;
	unsigned int	sn;
	unsigned int	meal_ctr;
	time_t			last_mealtime;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_data			*data;
} t_philo;

void	error_handler(char *msg, int cleanup);
void	data_init(t_data *data, char **nums);


void	philo_eat(t_philo *philo);
int		philo(t_data *data);
int		philo_init(t_philo **philo, t_data *data, t_fork **fork);
int		fork_init(t_fork **forks, t_data *data);
void	*check_forks(t_philo *philo);
void	philo_sleep(t_philo *philo);
bool	gonna_die(t_philo *philo);

#endif