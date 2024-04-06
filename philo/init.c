
#include "philo.h"

/**
 * @brief initializes the input struct
 * 
 * @param input input reference
 * @param nums nums 2d array
 */
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
	//free nums
}

/**
 * @brief initializes shared data struct
 * 
 * @param shared shared_data reference
 * @param input input reference
 * @return int 	if 1, success
 * 				if 0, failed
 */
bool	init_shared_data(t_shared_data *shared, t_input	*input)
{
	struct timeval	time_val;
	gettimeofday(&time_val, NULL);
	shared->simulation_start_time = (time_val.tv_sec * 1000) + (time_val.tv_usec/1000);
	shared->all_alive = true;
	shared->state_mutex = NULL;
	shared->print_mutex = NULL;
	if (pthread_mutex_init((shared->state_mutex), NULL))
	{
		printf("error\n"); //return 1 to not clean up anything
		return (0);
	}
	if (pthread_mutex_init((shared->print_mutex), NULL))
	{
		printf("error\n"); //return 2 to only destroy state_mutex
		return (0);
	}
	shared->input = input;
	return (1);
}

/**
 * @brief initializes the forks struct
 * 
 * @param forks reference to forks pointer
 * @param input reference to input
 * @return int 	the index that we free to
 * 				if 1, succeeds
 * 				if 0, fails
 */
bool	init_forks(t_fork **forks, t_input *input)
{
	int	i;

	i = -1;
	if (set_forks(forks, input->forks_num))
	{
		while (++i < input->forks_num)
		{
			forks[i] = malloc(sizeof(t_fork));
			if (!forks[i])
				return (0);
			forks[i]->sn = i + 1;
			forks[i]->in_use = false;
			forks[i]->last_user = 0;
			if (pthread_mutex_init((forks[i]->mutex), NULL))
			{
				printf("error\n");
				return (0);
			}
		}
		forks[i] = NULL;
	}
	return (1);
}

/**
 * @brief initializes the philosophers struct
 * 
 * @param philo reference to philo pointer
 * @param fork reference to forks pointer
 * @param input reference to input
 * @param shared reference to shared data
 * @return int 	the index that we free till
 * 				if 1, succeeds
 * 				if 0, fails
 */
bool	init_philos(t_philo  **philo, t_fork **fork, t_input *input, t_shared_data *shared)
{
	int	i;

	i = -1;
	set_philos(philo, input->philo_num);
	while (++i < input->philo_num)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (0);
		philo[i]->thread = malloc(sizeof(pthread_t));
		if (!philo[i]->thread)
			return (false);
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
		philo[i]->last_mealtime = 0;
	}
	philo[i] = NULL;
	return (1);
}
