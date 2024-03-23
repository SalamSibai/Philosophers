/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:01:38 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 17:15:36 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

char	*set_arg(char *str, int idx, int len)
{
	int		i;
	char	*arg;

	i = 0;
	arg = malloc((len + 1) * sizeof(char));
	if (!arg)
		return (NULL);
	while (i < len && str[idx])
		arg[i++] = str[idx++];
	arg[i] = '\0';
	return (arg);
}

int	set_args(char **split_args, char *str, int num)
{
	int	i;
	int begin;
	int	end;
	int	j;
	int	itr;

	begin = 0;
	end = 0;
	i = 0;
	itr = 0;
	while (i < num)
	{
		j = 0;
		begin = skip(str, 1, begin, 0);
		end = skip(str, 0, begin, 0);
		split_args[i] = set_arg(str, begin, end - begin);
		if (!split_args[i])
			return (0);
		i ++;
		begin = end;
	}
	split_args[num] = NULL;
	return (1);
}

char	**split_nums(char *av)
{
	char	**split_args;
	int		arg_num;

	arg_num = arg_ctr(av);
	if (arg_num == -1)
		return (parse_error("arguments are not all numbers\n", 0), NULL);
	else if (arg_num != 4 && arg_num != 5)
		return (parse_error("wrong number of arguments\n", 0), NULL);
	split_args = malloc((arg_num + 1) * sizeof (char*));
	if (!split_args)
		return (parse_error("no space\n", 0), NULL);
	if (!set_args(split_args, av, arg_num))
		return (parse_error("arguments couldn't be split\n", 0), NULL);
	return (split_args);
}
