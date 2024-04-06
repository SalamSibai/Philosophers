

#include "philo.h"

void    print_msg(t_philo *philo, char *msg, long timestamp)
{
	printf("time: %ld | Philosopher %d %s\n", timestamp ,philo->sn, msg);
}

void    print_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_data->print_mutex);
	print_msg(philo, "took a fork", philo->last_mealtime);
	pthread_mutex_unlock(philo->shared_data->print_mutex);
	pthread_mutex_lock(philo->shared_data->print_mutex);
	print_msg(philo, "took a fork", philo->last_mealtime);
	pthread_mutex_unlock(philo->shared_data->print_mutex);
	pthread_mutex_lock(philo->shared_data->print_mutex);
	print_msg(philo, "is eating", philo->last_mealtime);
	pthread_mutex_unlock(philo->shared_data->print_mutex);
}

void	print_sleeping(t_philo *philo, time_t	sleep_time)
{
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
