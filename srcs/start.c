/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:49:35 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 10:47:59 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_tokens *tokens, int argc, char *argv[])
{
	check_args(argc);
	tokens->file_in = argv[1];
	tokens->file_out = argv[argc - 1];
	check_input(tokens->file_in);
	tokens->processes_n = argc - 3;
	tokens->pipes = get_pipes(*tokens);
	tokens->pids = get_pids(*tokens);
	open_pipes(tokens->pipes);
}

int	*get_pids(t_tokens tokens)
{
	int	*pids;

	pids = malloc(sizeof(*pids) * tokens.processes_n);
	return (pids);
}

void	pipex_exec(t_tokens *tokens, char *argv[], char *envp[])
{
	int	process;

	process = 0;
	while (process < tokens->processes_n)
	{
		tokens->cmd = get_cmd(argv[process + 2]);
		if (get_path(tokens, tokens->cmd[0], envp)
			&& process == tokens->processes_n - 1)
			ft_printf("bash: %s: command not found\n", tokens->cmd[0]);
		tokens->pids[process] = fork();
		if (tokens->pids[process] == 0)
			exec_child(tokens, envp, process);
		clean_array(tokens->cmd);
		if (tokens->path)
			free(tokens->path);
		process++;
	}
}

void	exec_child(t_tokens *tokens, char *envp[], int process)
{
	close_child_pipes(tokens->pipes, process);
	if (process == 0)
		get_input(tokens->file_in, tokens->pipes[process]);
	else
		dup2(tokens->pipes[process][0], 0);
	close(tokens->pipes[process][0]);
	dup2(tokens->pipes[process + 1][1], 1);
	close(tokens->pipes[process + 1][1]);
	if (tokens->path)
		execve(tokens->path, tokens->cmd, envp);
	clean_array(tokens->cmd);
	free(tokens->pids);
	clean_pipes(tokens->pipes);
	exit(NOCMD);
}

int	wait_processes(t_tokens *tokens, int processes_n)
{
	int	process;
	int	status;
	int	status_code;

	process = 0;
	while (process < processes_n)
	{
		waitpid(tokens->pids[process], &status, 0);
		if (WIFEXITED(status))
		{
			if (process == processes_n - 1)
				status_code = WEXITSTATUS(status);
		}
		process++;
	}
	return (status_code);
}
