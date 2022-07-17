/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/17 13:58:54 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int 		i;
	t_tokens	tokens;
	
	i = 0;
	get_processesnum(&tokens, argc);
	tokens.pipes = get_pipes(tokens);
	tokens.pids = get_pids(tokens);
	open_pipes(tokens.pipes);
	while (i < tokens.processes_n)
	{
		tokens.pids[i] = fork();
		if (tokens.pids[i] == 0)
		{
			close_child_pipes(tokens.pipes, i);
			tokens.cmd = get_cmd(argv[i + 2]);
			dup2(tokens.pipes[i][0], 0);
			dup2(tokens.pipes[i + 1][1], 1);
			close(tokens.pipes[i][0]);
			close(tokens.pipes[i + 1][1]);
			execve(tokens.cmd[0], tokens.cmd, NULL);
		}
		i++;
	}
	close_main_pipes(tokens.pipes);
	get_input(argv[1], (tokens.pipes)[0]);
	get_output(argv[argc - 1], (tokens.pipes)[tokens.processes_n]);
	i = 0;
	while (i < tokens.processes_n)
	{
		wait(NULL);
		i++;
	}
	clean_pipes(tokens.pipes);
	free(tokens.pids);
	return 0;
}
