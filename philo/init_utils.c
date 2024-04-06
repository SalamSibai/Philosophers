
#include "philo.h"

void    set_forks(t_fork **forks, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		forks[i] = NULL;
		forks[i]->mutex = NULL;
	}
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