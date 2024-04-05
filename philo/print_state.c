

#include "philo.h"

void    print_msg(t_philo *philo, char *msg, long timestamp)
{
    printf("time: %ld | Philosopher %d %s\n", timestamp ,philo->sn, msg);
}

void    print_eatint(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
    print_msg(philo, "took a fork", philo->last_mealtime);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
    pthread_mutex_lock(&philo->shared_data->print_mutex);
    print_msg(philo, "took a fork", philo->last_mealtime);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
    pthread_mutex_lock(&philo->shared_data->print_mutex);
    print_msg(philo, "is eating", philo->last_mealtime);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}