/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:01:38 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/22 20:33:44 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

/// @brief skips spaces or numbers
/// @param av the argument
/// @param spaces flag, if 1 skips spaces, if 0 skips everything but spaces
/// @param i the index it starts from
int	skip(char *av, int spaces, int i)
{
	if (spaces)
	{
		while (av[i] == ' ' || (av[i] >= 9 && av[i] <= 13) && av[i] != '\0')
			i++;
	}
	else
	{
		while (av[i] != ' ' && !(av[i] >= 9 && av[i] <= 13) && av[i] != '\0')
			i++;
	}
	return (i);
}

int	arg_ctr(char *av)
{
	int	i;
	int	ctr;

	ctr = 0;
	i = 0;
	while (av[i] != '\0')
	{
		i = skip(av, 1, i);
		if (av[i] != '\0')
			ctr++;
		i = skip(av, 0, i);
	}
	return (ctr);
}

int	ft_atoi(char *av)
{
	
}

int	*split_nums(char *av)
{
	int		*nums;
	char	**split_args;

	split_args = malloc((arg_ctr(av) + 1) * sizeof (char*));
	if (!split_args)
		return (NULL);
	
}

int main (int ac, char **av)
{
	if (ac == 2)
	{
		printf("%d\n", arg_ctr(av[1]));
	}
}
