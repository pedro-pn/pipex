/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:18:41 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/15 15:45:42 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>
# include <stdio.h>

typedef struct s_tokens
{
	char	*file1;
	char	**cmd;
	char	*file2;
	int		processes_n;
}			t_tokens;

t_tokens	get_tokens(char *argv);
void	get_processesnum(t_tokens *tokens, int argc);
int		*get_pids(t_tokens tokens);
int 	**get_pipes(t_tokens tokens);
void	open_pipes(int **pipes);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes);
void	get_input(char *file_in, int *pipe);
void	get_output(char *file_out, int *pipe);

#endif
