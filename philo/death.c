

#include "philo.h"

/**
 * @brief check if it has been longer than death_time 
 * 		since the last mealtime
 * @param philo philo reference
 * @return true if a philo should die
 * @return false if a philo should live
 */
bool    should_die(t_philo *philo)
{
	struct timeval	tval;
	t_time_data		time_data;

	gettimeofday(&tval, NULL);
	time_data.curent = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
	time_data.last_meal = time_data.curent - philo->last_mealtime
		- philo->shared_data->start_time;
	if(time_data.last_meal > philo->shared_data->input->death_timer
		&& philo->last_mealtime != 0)
	{
		pthread_mutex_lock(&philo->shared_data->state_mutex);
		if (philo->shared_data->all_alive == false)
			pthread_mutex_unlock(&philo->shared_data->state_mutex);
		else
		{
			philo->shared_data->all_alive = false;
			pthread_mutex_unlock(&philo->shared_data->state_mutex);
			time_data.print = time_data.curent - philo->shared_data->start_time;
			philo->death_time = time_data.print;
		}
		return (true);
	}
	return (false);
}