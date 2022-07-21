/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:05:18 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/21 12:53:58 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc)
{
	if (argc < 5)
	{
		ft_printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
}

int	check_input(char *file_in)
{
	int	error;

	if (!ft_strncmp(file_in, "here_doc", ft_strlen(file_in)))
		return (TRUE);
	error = access(file_in, F_OK | R_OK);
	if (error != 0)
		ft_printf("bash: %s: %s\n", file_in, strerror(errno));
	return (FALSE);
}

void	pipe_error(t_data *data)
{
	clean_pipes(data->pipes);
	free(data->pids);
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	write(STDERR_FILENO, "Failed to alloc memory\n", 23);
	exit(EXIT_FAILURE);
}

void	process_error(t_data *data)
{
	int	index;

	index = 0;
	while (data->pipes[index])
	{
		close(data->pipes[index][0]);
		close(data->pipes[index][1]);
		index++;
	}
	clean_pipes(data->pipes);
	free(data->pids);
	if (data->path)
		free(data->path);
	clean_array(data->cmd);
	perror("pipex");
	exit(EXIT_FAILURE);
}
