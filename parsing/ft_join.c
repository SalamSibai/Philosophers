/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:08 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 21:28:20 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philo.h"

void	ft_copy(char *args, char *list, int *args_idx, int *list_idx)
{
	int	li;
	int	ai;

	li = *list_idx;
	ai = *args_idx;
	while (args[ai] != ' ' && !(args[ai] >= 9 && args[ai] <= 13)
		&& args[ai] != '\0')
	{
		list[li] = args[ai];
		ai ++;
		li ++;
		*list_idx = li;
		*args_idx = ai;
	}
}

char	*copy_to_list(char **args, int arg_num, int list_len)
{
	int		i;
	int		j;
	int		y;
	char	*list;

	i = 0;
	j = -1;
	y = 0;
	list = malloc ((list_len) * sizeof(char *));
	if (!list)
		return (NULL);
	memset(list, '\0', list_len);
	while (++j < arg_num)
	{
		y = 0;
		while (args[j][y] != '\0')
		{
			y = skip(args[j], 1, y, 0);
			ft_copy(args[j], list, &y, &i);
			y = skip(args[j], 1, y, 0);
			list[i++] = ' ';
		}
	}
	list[i] = '\0';
	return (list);
}

int	ft_listlen(char **av, int ac)
{
	int	len;
	int	i;
	int	j;
	int	end;

	i = 0;
	j = 0;
	len = 0;
	end = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			j = skip(av[i], 1, j, 0);
			end = skip(av[i], 0, j, 0);
			len += end - j;
			len ++;
			j = end;
		}
		i ++;
	}
	return (len);
}

bool	empty_str(char *args)
{
	int	spaces;

	spaces = skip(args, 1, 0, 0);
	if (spaces == ft_strlen(args))
		return (true);
	return (false);
}

char	*ft_join(char **args, int arg_num)
{
	char	*joined;
	int		list_len;
	int		i;

	i = -1;
	while (++i < arg_num)
	{
		if (empty_str(args[i]))
			return (error_msg("ERROR: empty string\n"), NULL);
	}
	list_len = ft_listlen(args, arg_num);
	joined = copy_to_list(args, arg_num, list_len);
	return (joined);
}
