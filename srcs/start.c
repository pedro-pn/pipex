/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:49:35 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 13:57:39 by ppaulo-d         ###   ########.fr       */
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

void	pipex_exec(t_tokens tokens, char *argv[], char *envp[])
{
	int	i;

	i = 0;
	while (i < tokens.processes_n)
	{
		tokens.pids[i] = fork();
		if (tokens.pids[i] == 0)
		{
			close_child_pipes(tokens.pipes, i);
			if (i == 0)
				get_input(tokens.file_in, tokens.pipes[i]);
			else
				dup2(tokens.pipes[i][0], 0);
			tokens.cmd = get_cmd(argv[i + 2]);
			tokens.path = get_path(tokens.cmd[0]);
			close(tokens.pipes[i][0]);
			dup2(tokens.pipes[i + 1][1], 1);
			close(tokens.pipes[i + 1][1]);
			execve(tokens.path, tokens.cmd, NULL);
		}
		i++;
	}
}

void	wait_processes(int processes_n)
{
	int	i;

	i = 0;
	while (i < processes_n)
	{
		wait(NULL);
		i++;
	}
}
