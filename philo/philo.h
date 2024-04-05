

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
}	t_philo;


#endif