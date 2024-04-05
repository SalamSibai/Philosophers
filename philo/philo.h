

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

typedef	struct s_error_codes
{
	int	shared_data_error;
	int	forks_error;
	int	philos_error;
}	t_error_code;

typedef	struct s_time_data
{
	time_t	curent;
	time_t	print;
	time_t  last_meal;
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
	time_t			start_time;
	pthread_mutex_t	state_mutex;
	bool			all_alive;
	pthread_mutex_t	print_mutex;
	t_input			*input;
}	t_shared_data;


typedef	struct s_fork
{
	int				sn;
	pthread_mutex_t	mutex;
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
void	init_error_codes(t_error_code *error);
int     init_shared_data(t_shared_data *shared_data, t_input *input);
int     init_forks(t_fork **forks, t_input *input);

/* ************************************************************************** */
/*							    	PHILOSOPHERS 	                          */
/* ************************************************************************** */

int		philo(t_input *input);
void	*find_forks(t_philo *philo);
bool    should_die(t_philo	*philo);
void	print_eating(t_philo *philo);

/* ************************************************************************** */
/*							    	ERROR HANDLING 	                          */
/* ************************************************************************** */

void	error_handler(int	philo_setup);

#endif