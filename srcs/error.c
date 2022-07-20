/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:05:18 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 14:43:01 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc)
{
	if (argc < 5)
	{
		ft_printf("Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
}

void	check_input(char *file_in)
{
	int	error;

	error = access(file_in, F_OK | R_OK);
	if (error != 0)
		ft_printf("bash: %s: %s\n", file_in, strerror(errno));
}
