/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:02:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/22 11:41:56 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Alloc memory for pipes
int	**get_pipes(t_data *data)
{
	int	index;
	int	**pipes;

	index = 0;
	pipes = malloc(sizeof(*pipes) * (data->processes_n + 2));
	if (!pipes)
		error_handle(data, MALLOC_ERROR);
	data->pipes[data->processes_n + 1] = NULL;
	while (index < data->processes_n + 1)
	{
		pipes[index] = malloc(2 * sizeof(**pipes));
		if (!pipes[index])
			error_handle(data, MALLOC_ERROR);
		index++;
	}
	return (pipes);
}

int	open_pipes(t_data *data)
{
	int	index;

	index = 0;
	while (data->pipes[index])
	{
		if (pipe(data->pipes[index]) == -1)
			error_handle(data, PIPE_ERROR);
		index++;
	}
	return (0);
}

void	close_child_pipes(int **pipes, int process)
{
	int	index;

	index = 0;
	while (pipes[index])
	{
		if (index != process)
			close(pipes[index][0]);
		if (index != process + 1)
			close(pipes[index][1]);
		index++;
	}
}

void	close_main_pipes(int **pipes, int here_doc)
{
	int	index;

	index = 0;
	while (pipes[index + 1])
	{
		close(pipes[index][0]);
		if (!(index == 1 && here_doc == 1))
			close(pipes[index][1]);
		index++;
	}
	close(pipes[index][1]);
}
