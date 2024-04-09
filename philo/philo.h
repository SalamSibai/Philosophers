/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:24:36 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:25:41 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "../parsing/parsing.h"

typedef struct s_time_data
{
	time_t	curent;
	time_t	print;
	time_t	last_meal;
	time_t	start_doing;
	time_t	doing_elapsed;
}	t_time_data;

typedef struct s_input
{
	int				philo_num;
	int				forks_num;
	int				death_timer;
	int				food_timer;
	int				sleep_timer;
	int				food_ctr;
}	t_input;

typedef struct s_shared_data
{
	time_t			simulation_start_time;
	pthread_mutex_t	*state_mutex;
	bool			all_alive;
	pthread_mutex_t	*full_mutex;
	int				full_ctr;
	pthread_mutex_t	*print_mutex;
	t_input			*input;
}	t_shared_data;

typedef struct s_fork
{
	int				sn;
	pthread_mutex_t	*mutex;
	bool			in_use;
	int				last_user;
}	t_fork;

typedef struct s_philo
{
	int				sn;
	pthread_t		*thread;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				meal_ctr;
	int				death_time;
	t_shared_data	*shared_data;
	time_t			last_mealtime;
	bool			count_meals;
}	t_philo;

/* ************************************************************************** */
/*									INITIALIZING							  */
/* ************************************************************************** */

bool	init_input(t_input *input, char **nums);
bool	init_shared_data(t_shared_data *shared, t_input	*input);
bool	init_forks(t_fork **forks, t_input *input);
void	init_philo_utils(t_philo **philo, t_fork **fork, t_input *input, int i);
bool	init_philos(t_philo **phi, t_fork **f, t_input *in, t_shared_data *srd);
void	init_forks_utils(t_fork *fork, int i);
void	set_fork(t_fork *fork);
void	set_philo(t_philo *philo);

/* ************************************************************************** */
/*									PHILOSOPHERS							  */
/* ************************************************************************** */

int		philo(t_input *input);
void	*start_sim(t_philo *philo);
bool	find_forks(t_philo *philo);
bool	philo_eat(t_philo *philo);
bool	use_forks(t_philo *philo);
void	leave_forks(t_philo *philo);
void	increment_meals_eaten(t_philo *philo);
bool	philo_think(t_philo *philo);
bool	should_die(t_philo	*philo);
bool	doing(t_philo *philo, time_t time_it_takes);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo, time_t	sleep_time);
void	print_thinking(t_philo *philo, time_t	think_time);
void	print_dead(t_philo	*philo);
bool	philo_sleep(t_philo *philo);

/* ************************************************************************** */
/*									ERROR HANDLING							  */
/* ************************************************************************** */

void	clean_philos(t_philo **philos, int index, bool end);
void	clean_forks(t_fork	**forks, int index, bool end);
bool	clean_input(t_input	*input);
void	error_msg(char *msg);
void	clean_share_data(t_shared_data *shared_data, int mutex_sn);
void	cleanup(t_philo **philo, t_fork **fork, t_shared_data *shared);

#endif