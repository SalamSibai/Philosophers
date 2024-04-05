
#include "philo.h"

void	init_input(t_input *input, char  **nums)
{
	input->philo_num = ft_atol(nums[0]);
	if (input->philo_num == -1)
		printf("error\n"); //and return
	input->forks_num = input->philo_num;
	input->death_timer = ft_atol(nums[1]);
	if (input->death_timer == -1)
		printf("error\n");
	input->food_timer = ft_atol(nums[2]);
	if (input->food_timer == -1)
		printf("error\n");
	input->sleep_timer = ft_atol(nums[3]);
	if (input->sleep_timer == -1)
		printf("error\n");
	if (tot_vars(nums) == 5)
	{
		input->food_ctr = ft_atol(nums[4]);
		if (input->food_ctr == -1)
			printf("error\n");
	}
	else
	input->food_ctr = -1;
}

int     init_shared_data(t_shared_data *shared_data)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	shared_data->start_time = (time_val.tv_sec * 1000) + (time_val.tv_usec/1000);
	shared_data->all_alive = true;
	if (pthread_mutex_init(&(shared_data->state_mutex), NULL))
		printf("error\n"); //return 1 to not clean up anything
	if (pthread_mutex_init(&(shared_data->print_mutex), NULL))
		printf("error\n"); //return 2 to only destroy state_mutex
	return (0);
}

int     init_fork(t_fork **forks, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->forks_num)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (i - 1); // the index we must free until
							// if -1, the first fork failed, we free nothing
		forks[i]->sn = i + 1;
		forks[i]->in_use = false;
		forks[i]->last_user = 0;
		if (pthread_mutex_inti(&(forks[i]->mutex), NULL))
		{
			printf("error\n");
			return (i); // the index we must free until
						// if i that is returned is 0:
						// means we only free the first index of fork, without destroying the mutex
						// for mutexes: we always destroy i - 1 mutexes
		}
	}
	forks[i] = NULL;
	return (0);
}

int     init_philos(t_philo  **philo, t_fork **fork, t_input *input, t_shared_data *shared)
{
	int	i;

	i = -1;
	while (++i < input->philo_num)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (i - 1); // the index we must free until
							// if -1, the first philo failed, we free nothing
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (!philo[i]->thread)
			return (i); // the index we must free until
						// if i that is returned is 0:
						// means we only free the first index of fork, without freeing the thread
						// for threads: we always free i - 1 thread
		philo[i]->sn = i + 1;
		philo[i]->state = ALIVE;
		if (i == 0)
			philo[i]->l_fork = fork[input->forks_num - 1];
		else
			philo[i]->l_fork = fork[i - 1];
		philo[i]->r_fork = fork[i];
		philo[i]->meal_ctr = 0;
		philo[i]->death_time = -1;
		philo[i]->shared_data = shared;
	}
	philo[i] = NULL;
	return (0);
}

