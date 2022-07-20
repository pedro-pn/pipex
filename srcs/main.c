/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 14:15:53 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	int		exit_status;

	pipex_init(&data, argc, argv);
	pipex_exec(&data, argv, envp);
	close_main_pipes(data.pipes);
	exit_status = wait_processes(&data, data.processes_n);
	if (get_output(data.file_out, (data.pipes)[data.processes_n]) == -1)
		exit_status = 1;
	clean_pipes(data.pipes);
	free(data.pids);
	if (exit_status != 0)
		exit(exit_status);
	exit(EXIT_SUCCESS);
}
