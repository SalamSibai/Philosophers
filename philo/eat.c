

#include "philo.h"




void    grab_forks(t_philo  *philo, bool left)
{
	if (left)
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->l_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		pthread_mutex_lock(&philo->r_fork->mutex);
	}
}





void    leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
}





bool    take_forks(t_philo *philo)
{
	bool    l_available;
	bool    r_available;

	l_available = true;
	r_available = true;
	if (!philo->r_fork->in_use && !philo->l_fork->in_use)
	{
		if (philo->r_fork->last_user != 0)
		{
			if (philo->r_fork->last_user != philo->sn)
				r_available = true;
			else
				r_available = false;
		}
		if (philo->l_fork->last_user != 0)
		{
			if (philo->l_fork->last_user != philo->sn)
				l_available = true;
			else
				l_available = false;
		}
		return (r_available && l_available);
	}
	return (false);
}






bool	philo_eat(t_philo	*philo)
{
	struct timeval	tval;
	t_time_data		time_data;

	pthread_mutex_lock(&philo->shared_data->state_mutex);
	if (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(&philo->shared_data->state_mutex);
		gettimeofday(&tval, NULL);
		time_data.last_meal = (tval.tv_sec * 1000) + (tval.tv_usec/1000);
		time_data.print = time_data.last_meal - philo->shared_data->start_time;
		philo->last_mealtime = time_data.print;
		print_eating(philo);
		//dream loop
		if (philo->sn == philo->shared_data->input->philo_num)
			grab_forks(philo, true);
		else
			grab_forks(philo, false);
		philo->l_fork->in_use = 0;
		philo->r_fork->in_use = 0;
		leave_forks(philo);
		//sleep
	}
	else
	{
		pthread_mutex_unlock(&philo->shared_data->state_mutex);
		return (false);
	}
	return (true);
}





void    *find_forks(t_philo *philo)
{    
	pthread_mutex_lock(&philo->shared_data->state_mutex);
	while (philo->shared_data->all_alive)
	{
		pthread_mutex_unlock(&philo->shared_data->state_mutex);
		if (should_die(philo))
			return (NULL);
		if (philo->sn == philo->shared_data->input->philo_num)
			grab_forks(philo, true);
		else
			grab_forks(philo, false);
		if (take_forks)
		{
			philo->r_fork->in_use = 1;
			philo->l_fork->in_use = 1;
			leave_forks(philo);
			philo_eat(philo);
		}
		else
			leave_forks(philo);
		pthread_mutex_lock(&philo->shared_data->state_mutex);
	}
	pthread_mutex_unlock(&philo->shared_data->state_mutex);
	return (NULL); //-1 means someone died already
}