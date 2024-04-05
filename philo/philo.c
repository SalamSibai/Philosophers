
#include "philo.h"

int	make_philosophers(t_philo **philos, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->philo_num)
		pthread_create(philos[i]->thread, NULL, (void *)&find_forks, philos[i]);
}


int philo(t_input *input)
{
	t_philo			**philos;
	t_fork			**forks;
	t_shared_data	*shared_data;
	t_error_code	*error;

	error = malloc(sizeof(t_error_code));
	if (!error)
		return (1); //failed and shouldn't free anything
	shared_data = malloc(sizeof(t_shared_data));
	if (!shared_data)
		return (2); //failed and should free error 
	error->shared_data_error = init_shared_data(shared_data, input);
	if (error->shared_data_error)
	{
		if (error->shared_data_error == 2)
			pthread_mutex_destroy(&(shared_data->state_mutex));
		return (3); //failed and should free both shared data and error
	}
	forks = malloc(sizeof(t_fork *) * (input->forks_num + 1));
	if (!forks)
	{
		//destroy mutexes
		return (3); //failed and should free both shared data and error
	}
	error->forks_error = init_forks(forks, input);
	if (error->forks_error > -2)
	{
		if (error->forks_error == -1)
			return (4); //failed and should free both shared data and error and forks
		//else
		// we free forks till error->forks_error
		// we destroy mutex error->forks_error - 1	
	}
	philos = malloc(sizeof(t_philo *) * (input->philo_num + 1));
	if (!philos)
	{
		//destroy mutexes
		return (4); //failed and should free both shared data and error and forks
	}
	error->philos_error = init_philos(philos, forks, input, shared_data);
	if (error->philos_error > -2)
	{
		//destroy mutexes
		if (error->philos_error == -1)
			return (5); // faild and shoudld free shared data, error, forks, and philos
		//else
		// we free philos till error->forks_error
		// we free philos->thread error->forks - 1
	}
	make_philosophers(philos, input);

	return (0);
}