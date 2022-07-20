/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:49:35 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 14:14:57 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_data *data, int argc, char *argv[])
{
	check_args(argc);
	data->file_in = argv[1];
	data->file_out = argv[argc - 1];
	check_input(data->file_in);
	data->processes_n = argc - 3;
	data->pipes = get_pipes(*data);
	data->pids = get_pids(*data);
	open_pipes(data->pipes);
}

int	*get_pids(t_data data)
{
	int	*pids;

	pids = malloc(sizeof(*pids) * data.processes_n);
	return (pids);
}

void	pipex_exec(t_data *data, char *argv[], char *envp[])
{
	int	process;

	process = 0;
	while (process < data->processes_n)
	{
		data->cmd = get_cmd(argv[process + 2]);
		if (get_path(data, data->cmd[0], envp)
			&& process == data->processes_n - 1)
			ft_printf("%s: command not found\n", data->cmd[0]);
		data->pids[process] = fork();
		if (data->pids[process] == 0)
			exec_child(data, envp, process);
		clean_array(data->cmd);
		if (data->path)
			free(data->path);
		process++;
	}
}

void	exec_child(t_data *data, char *envp[], int process)
{
	close_child_pipes(data->pipes, process);
	if (process == 0)
		get_input(data->file_in, data->pipes[process]);
	else
		dup2(data->pipes[process][0], 0);
	close(data->pipes[process][0]);
	dup2(data->pipes[process + 1][1], 1);
	close(data->pipes[process + 1][1]);
	if (data->path)
		execve(data->path, data->cmd, envp);
	clean_array(data->cmd);
	free(data->pids);
	clean_pipes(data->pipes);
	exit(NOCMD);
}

int	wait_processes(t_data *data, int processes_n)
{
	int	process;
	int	status;
	int	status_code;

	process = 0;
	while (process < processes_n)
	{
		waitpid(data->pids[process], &status, 0);
		if (WIFEXITED(status))
		{
			if (process == processes_n - 1)
				status_code = WEXITSTATUS(status);
		}
		process++;
	}
	return (status_code);
}
