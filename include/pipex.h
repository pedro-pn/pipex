/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:18:41 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:39:59 by ppaulo-d         ###   ########.fr       */
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
# include <string.h>

# define NOCMD 127

typedef struct s_tokens
{
	char	**cmd;
	char	*path;
	char	*file_in;
	char	*file_out;
	int		**pipes;
	int		*pids;
	int		processes_n;
}			t_tokens;

char	**get_cmd(char *argv);
int		*get_pids(t_tokens tokens);
int		**get_pipes(t_tokens tokens);
void	open_pipes(int **pipes);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes);
void	get_input(char *file_in, int *pipe);
int		get_output(char *file_out, int *pipe);
void	clean_pipes(int **pipes);
void	pipex_init(t_tokens *tokens, int argc, char *argv[]);
void	pipex_exec(t_tokens *tokens, char *argv[], char *envp[]);
int		wait_processes(t_tokens *tokens, int processes_n);
void	check_args(int argc);
int		open_file(t_tokens tokens);
void	check_input(char *file_in);
int		get_path(t_tokens *tokens, char *cmd, char *envp[]);
void	clean_array(char **array);
void	exec_child(t_tokens *tokens, char *envp[], int process);
int		check_path(t_tokens *tokens, char **bin_paths, char *cmd);
void	clean_quotes(char *argv);

#endif
