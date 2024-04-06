

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

typedef	enum	e_state
{
	ALIVE,
	DEAD
} t_state;

typedef	struct s_time_data
{
	time_t	curent;
	time_t	print;
	time_t  last_meal;
	time_t	start_doing;
	time_t	doing_elapsed;
}	t_time_data;


typedef	struct s_input
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
	pthread_mutex_t	*print_mutex;
	t_input			*input;
}	t_shared_data;


typedef	struct s_fork
{
	int				sn;
	pthread_mutex_t	*mutex;
	bool			in_use;
	int				last_user;
}	t_fork;

typedef	struct s_philo
{
	int				sn;
	pthread_t		*thread;
	t_state			state;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				meal_ctr;
	int				death_time;
	t_shared_data	*shared_data;
	time_t			last_mealtime;
}	t_philo;

/* ************************************************************************** */
/*      							INITIALIZING				 	          */
/* ************************************************************************** */

void	init_input(t_input *input, char  **nums);
bool    init_shared_data(t_shared_data *shared_data, t_input *input);
bool    init_forks(t_fork **forks, t_input *input);
bool	init_philos(t_philo  **philo, t_fork **fork, t_input *input, t_shared_data *shared);
bool	set_forks(t_fork **forks, int size);
void	set_philos(t_philo **philos, int size);

/* ************************************************************************** */
/*							    	PHILOSOPHERS 	                          */
/* ************************************************************************** */

int		philo(t_input *input);
void	*find_forks(t_philo *philo);
bool    should_die(t_philo	*philo);
bool	doing(t_philo   *philo, time_t  time_it_takes);
void	print_eating(t_philo *philo);
void	print_sleeping(t_philo *philo, time_t	sleep_time);
void	print_thinking(t_philo *philo, time_t	think_time);
void	print_dead(t_philo	*philo);

/* ************************************************************************** */
/*							    	ERROR HANDLING 	                          */
/* ************************************************************************** */

bool	clean_philos(t_philo **philos);
bool	clean_shared_data(t_shared_data *shared);
bool	clean_forks(t_philo	**forks);
bool	clean_input(t_input	*input);
void	error_handler(char *error_msg);

#endif