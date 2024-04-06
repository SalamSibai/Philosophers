
#include "philo.h"

int	make_philosophers(t_philo **philos, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->philo_num)
		pthread_create(philos[i]->thread, NULL, (void *)&find_forks, philos[i]);
	i = -1;
	while (++i < input->philo_num)
		pthread_join(*philos[i]->thread, NULL);
	if (!philos[0]->shared_data->all_alive)
	{
		i = -1;
		while (++i < input->philo_num)
		{
			if (philos[i]->death_time != -1)
			{
				print_dead(philos[i]);
				break;
			}
		}
	}
	return (1);
}


int philo(t_input *input)
{
	t_philo			**philos;
	t_fork			**forks;
	t_shared_data	*shared_data;

	philos = NULL;
	forks = NULL;
	shared_data = NULL;
	shared_data = malloc(sizeof(t_shared_data));
	if (!shared_data)
		return (0); //print error msg firs (NO SPACE for shared data)
	if (!init_shared_data(shared_data, input))
		return (0); //print error msg firs (NO SPACE for shared data)
	forks = malloc(sizeof(t_fork *) * (input->forks_num + 1));
	if (!forks)
		return (0); //print error msg firs (NO SPACE for forks)
	if (!init_forks(forks, input))
		return (0); //print error msg firs (NO SPACE for forks)
	philos = malloc(sizeof(t_philo *) * (input->philo_num + 1));
	if (!philos)
		return (0); //print error msg firs (NO SPACE for philos)
	if (!init_philos(philos, forks, input, shared_data))
		return (0); //print error msg firs (NO SPACE for philos)
	make_philosophers(philos, input);
	return (1);
}