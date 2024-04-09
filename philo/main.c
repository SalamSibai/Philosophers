/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:56:40 by ssibai            #+#    #+#             */
/*   Updated: 2024/04/09 17:56:43 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_input	*input;
	char	**nums;

	nums = validate(ac-1, av);
	if (!nums)
		return (0);
	input = malloc (sizeof(t_input));
	if (!input)
	{
		free_matrix(nums);
		error_msg("Error: no space for input\n");
		return (0);
	}
	if (!init_input(input, nums))
	{
		free_matrix(nums);
		free (input);
		return (0);
	}
	philo(input);
	free(input);
	return (0);
}