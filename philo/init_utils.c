
#include "philo.h"

bool    set_forks(t_fork **forks, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		forks[i] = NULL;
		forks[i]->mutex = NULL;
	}
	return (true);
}

void    set_philos(t_philo **philos, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		philos[i] = NULL;
		philos[i]->thread = NULL;
	}
}
