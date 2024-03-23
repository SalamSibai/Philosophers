/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:36 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 17:56:19 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

int	tot_vars(char **av)
{
	int	ctr;

	ctr = 0;
	while (av[ctr] != NULL)
		ctr ++;
	return (ctr);
}

/// @brief skips spaces or numbers
/// @param av the argument
/// @param spaces flag, if 1 skips spaces, if 0 skips everything but spaces
/// @param i the index it starts from
/// @param check_num flag, checkes if the character sent is a number or not
int	skip(char *av, int spaces, int i, int check_num)
{
	if (spaces)
	{
		while ((av[i] == ' ') || ((av[i] >= 9 && av[i] <= 13) && (av[i] != '\0')))
			i++;
	}
	else
	{
		while ((av[i] != ' ') && (!(av[i] >= 9 && av[i] <= 13)) && (av[i] != '\0'))
		{
			if (check_num)
			{
				if (!validate_num(av[i]))
				{
					printf("not valid\n");
					return (-1);
				}
			}
			i++;
		}
	}
	return (i);
}

/// @brief counts number of arguments in a string.
/// @param av the string
/// @return number of args
int	arg_ctr(char *av)
{
	int	i;
	int	ctr;

	ctr = 0;
	i = 0;
	while (av[i] != '\0')
	{
		i = skip(av, 1, i, 0);
		if (av[i] != '\0')
			ctr++;
		i = skip(av, 0, i, 1);
		if (i == -1)
			return (-1);
	}
	return (ctr);
}
