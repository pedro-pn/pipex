/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/15 16:00:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define PROCESS 3

int	main(int argc, char *argv[])
{
	int			**pipes;
	int			*pids;
	int 		i;
	t_tokens	tokens;
	
	i = 0;
	get_processesnum(&tokens, argc);
	pipes = get_pipes(tokens);
	pids = get_pids(tokens);
	open_pipes(pipes);
	while (i < tokens.processes_n)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{

			close_child_pipes(pipes, i);
			tokens = get_tokens(argv[i + 2]);
			dup2(pipes[i][0], 0);
			dup2(pipes[i + 1][1], 1);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			execve(tokens.cmd[0], tokens.cmd, NULL);
		}
		i++;
	}
	close_main_pipes(pipes);
	get_input(argv[1], pipes[0]);
	get_output(argv[argc - 1], pipes[tokens.processes_n]);
	return 0;
}
