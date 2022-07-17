/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/17 20:30:16 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_tokens	tokens;

	pipex_init(&tokens, argc);
	pipex_exec(tokens, argv);
	close_main_pipes(tokens.pipes);
	get_input(argv[1], (tokens.pipes)[0]);
	get_output(argv[argc - 1], (tokens.pipes)[tokens.processes_n]);
	wait_processes(tokens.processes_n);
	clean_pipes(tokens.pipes);
	free(tokens.pids);
	return (0);
}
