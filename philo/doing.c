

#include "philo.h"

bool	doing(t_philo *philo, time_t time_it_takes)
{
	struct timeval  tval;
	t_time_data     time_data;

	gettimeofday(&tval, NULL);
	time_data.start_doing = (tval.tv_sec * 1000) * (tval.tv_usec / 1000);
	time_data.doing_elapsed = time_data.start_doing;
	while ((time_data.doing_elapsed - time_data.start_doing < time_it_takes))
	{
		if (should_die(philo))
			return (false);
		else
		{
			pthread_mutex_lock(philo->shared_data->state_mutex);
			if (philo->shared_data->all_alive)
			{
				pthread_mutex_unlock(philo->shared_data->state_mutex);
				usleep(100);
			}
			else
			{
				pthread_mutex_unlock(philo->shared_data->state_mutex);
				return (false);
			}
			gettimeofday(&tval, NULL);
			time_data.doing_elapsed = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		}
	}
	return (true);
}
