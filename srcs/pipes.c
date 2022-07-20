/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:02:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 14:15:00 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Alloc memory for pipes
int	**get_pipes(t_data data)
{
	int	index;
	int	**pipes;

	index = 0;
	pipes = malloc(sizeof(*pipes) * (data.processes_n + 2));
	pipes[data.processes_n + 1] = NULL;
	while (index < data.processes_n + 1)
	{
		pipes[index] = malloc(2 * sizeof(**pipes));
		index++;
	}
	return (pipes);
}

void	open_pipes(int **pipes)
{
	int	index;

	index = 0;
	while (pipes[index])
	{
		pipe(pipes[index]);
		index++;
	}
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

void	close_main_pipes(int **pipes)
{
	int	index;

	index = 0;
	while (pipes[index + 1])
	{
		close(pipes[index][0]);
		close(pipes[index][1]);
		index++;
	}
	close(pipes[index][1]);
}

void	clean_pipes(int **pipes)
{
	int	index;

	index = 0;
	while (pipes[index])
	{
		free(pipes[index]);
		index++;
	}
	free(pipes);
}
