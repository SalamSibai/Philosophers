
#include "philo.h"

void	clean_forks(t_fork **forks, int index, bool end)
{
	int	i;

	i = -1;
	if (index == -1)
		return;
	else
	{
		while (++i < index)
		{
			free(forks[i]);
			if (!end)
			{
				if (i > 0)
					free(forks[i - 1]->mutex);
			}
			else
				free(forks[i]->mutex);
		}
	}
	free (forks);
}

void	clean_philos(t_philo **philos, int index, bool end)
{
	int	i;

	i = -1;
	if (index == -1)
		return;
	else
	{
		while (++i < index)
		{
			free(philos[i]);
			if (!end)
			{
				if (i > 0)
					free(philos[i - 1]->thread);
			}
			else
				free(philos[i]->thread);
		}
	}
	free(philos);
}
