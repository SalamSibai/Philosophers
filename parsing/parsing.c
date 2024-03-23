/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:48:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/22 20:01:45 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philo.h"

int	validate_num(char	str)
{
	if (!(str >= 48 && str <= 57))
		return (0);
	return (1);
}

int	ft_atol(char *str)
{
	
}

int	validate(int ac, char **av)
{
	if (ac == 1)
	{
		//must split all, count and then store each number properly
	}
	else
	{
		//must be at least 5, i can check for each string the number of stuff and then store in proper places
	}
}