/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 20:12:14 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_tokens	tokens;
	int			exit_status;

	pipex_init(&tokens, argc, argv);
	pipex_exec(&tokens, argv, envp);
	close_main_pipes(tokens.pipes);
	exit_status = wait_processes(&tokens, tokens.processes_n);
	ft_printf("exit anaates: %d\n", exit_status);
	if (get_output(tokens.file_out, (tokens.pipes)[tokens.processes_n]) == -1)
		exit_status = 1;
	clean_pipes(tokens.pipes);
	free(tokens.pids);
	ft_printf("exit depois: %d\n", exit_status);
	if (exit_status != 0)
		exit(exit_status);
	// else if (errno != 0)
	// 	exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
// exit code sempre é do ultimo executavel
// mesmo se o infile falhar (menor prioridade)
// se o output falhar, seu exit code substitui o do ultimo comando