

#include "philo.h"

void	print_msg(t_philo *philo, char *msg, long timestamp)
{

	pthread_mutex_lock(philo->shared_data->print_mutex);
	printf("time: %ld | Philosopher %d %s\n", timestamp ,philo->sn, msg);
	pthread_mutex_unlock(philo->shared_data->print_mutex);
}

void	print_eating(t_philo *philo)
{
	print_msg(philo, "took a fork", philo->last_mealtime);
	print_msg(philo, "took a fork", philo->last_mealtime);
	print_msg(philo, "is eating", philo->last_mealtime);
}

void	print_sleeping(t_philo *philo, time_t	sleep_time)
{
		pthread_mutex_unlock(philo->shared_data->state_mutex);
		print_msg(philo, "is sleeping", sleep_time);
}

void	print_thinking(t_philo *philo, time_t	think_time)
{

		print_msg(philo, "is thinking", think_time);
}

void	print_dead(t_philo	*philo)
{
	print_msg(philo, "is dead", philo->death_time);
}
