/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:48:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 18:06:18 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

int	validate_num(char	str)
{
	if (!(str >= 48 && str <= 57))
		return (0);
	return (1);
}

int	ft_atol(char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 0)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (-1);
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (num > 2147483647)
		return (-1);
	return (num);
}

char	**validate(int ac, char **av)
{
	char	**num_str;
	char	*joined;

	if (ac == 1)
	{
		num_str = split_nums(av[1]);
		if (!num_str)
		{
			//make sure u free
			return (NULL);
		}
	}
	else
	{
		joined = ft_join(++av, ac);
		if (!joined)
			return (NULL);
		num_str = split_nums(joined);
		if (!num_str)
		{
			free (joined);
			//make sure u free
			return (NULL);
		}
	}
	return (num_str);
}