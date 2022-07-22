/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:05:18 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/22 11:38:40 by ppaulo-d         ###   ########.fr       */
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

void	error_handle(t_data *data, int code)
{
	if (code == PIPE_ERROR)
		perror("pipex");
	else if (code == MALLOC_ERROR)
		write(STDERR_FILENO, "Failed to alloc memory\n", 23);
	else if (code == PROCESS_ERROR)
		perror("pipex");
	clean_data(data);
	exit(EXIT_FAILURE);
}

void	clean_data(t_data *data)
{
	int index;

	index = 0;
	if (data->pids)
		free(data->pids);
	if (data->cmd)
		clean_array((void **)data->cmd);
	if(data->pipes)
	{
		while (data->pipes[index])
		{
			close(data->pipes[index][0]);
			close(data->pipes[index][1]);
			index++;
		}
		clean_array((void **)data->pipes);
	}
	
}