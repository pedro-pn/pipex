/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:49:35 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 20:13:59 by ppaulo-d         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < tokens->processes_n)
	{
		tokens->cmd = get_cmd(argv[i + 2]);
		if (get_path(tokens, tokens->cmd[0], envp) && i == tokens->processes_n - 1)
			ft_printf("bash: %s: command not found\n", tokens->cmd[0]);
		tokens->pids[i] = fork();
		if (tokens->pids[i] == 0)
		{
			close_child_pipes(tokens->pipes, i);
			if (i == 0)
				get_input(tokens->file_in, tokens->pipes[i]);
			else
				dup2(tokens->pipes[i][0], 0);
			close(tokens->pipes[i][0]);
			dup2(tokens->pipes[i + 1][1], 1);
			close(tokens->pipes[i + 1][1]);
			if (tokens->path)
				execve(tokens->path, tokens->cmd, NULL);
			clean_array(tokens->cmd);
			free(tokens->pids);
			clean_pipes(tokens->pipes);
			exit(127);
		}
		clean_array(tokens->cmd);
		if (tokens->path)
			free(tokens->path);
		i++;
	}
}

int	wait_processes(t_tokens *tokens, int processes_n)
{
	int	i;
	int	status;
	int	status_code;
	
	i = 0;
	while (i < processes_n)
	{
		waitpid(tokens->pids[i], &status, 0); // waitpid espera na ordem correta
		if (WIFEXITED(status))
		{
			if (i == processes_n - 1)
				status_code = WEXITSTATUS(status); // pega ultimo status code
		//	ft_printf("dentro do wait: %d\ti: %d\n", status_code, i);
		}
		i++;
	}
	//ft_printf("dentro: %d\n", status_code);
	// if (status_code == 127)
	// 	return (status_code);
	return (status_code);
}
