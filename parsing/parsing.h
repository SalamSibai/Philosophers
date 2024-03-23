/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:11:51 by ssibai            #+#    #+#             */
/*   Updated: 2024/03/23 18:00:44 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**validate(int ac, char **av);
char	*ft_join(char **args, int arg_num);
char	**split_nums(char *av);
int		arg_ctr(char *av);
int		skip(char *av, int spaces, int i, int check_num);
int		validate_num(char	str);
void	parse_error(char *msg, int cleanup);
int		tot_vars(char **av);
int		ft_atol(char *str);

#endif