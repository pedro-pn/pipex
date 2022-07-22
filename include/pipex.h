/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:18:41 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/22 11:43:49 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"

# define NOCMD 127
# define TRUE 1
# define FALSE 0
# define MALLOC_ERROR 1
# define PIPE_ERROR 2
# define PROCESS_ERROR 3

typedef struct s_data
{
	char	**cmd;
	char	*path;
	char	*file_in;
	char	*file_out;
	int		**pipes;
	int		*pids;
	int		processes_n;
	int		here_doc;
}			t_data;

// pipex_init

void	pipex_init(t_data *data, int argc, char *argv[]);

// processes functions

int		*get_pids(t_data *data);
void	pipex_exec(t_data *data, char *argv[], char *envp[]);
void	exec_child(t_data *data, char *envp[], int process);
int		wait_processes(t_data *data, int processes_n);
// Parser functions

char	**get_cmd(char *argv);
int		get_path(t_data *data, char *cmd, char *envp[]);
int		check_path(t_data *data, char **bin_paths, char *cmd);
void	clean_quotes(char *argv);
void	clean_array(void **array);
// Pipes functions

int		**get_pipes(t_data *data);
int		open_pipes(t_data *data);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes, int here_doc);
// i/o files functions

void	get_input(char *file_in, int *pipe);
void	get_user_input(t_data *data, char *delimiter);
int		get_output(char *file_out, int *pipe, int here_doc);

// error functions

void	error_handle(t_data *data, int code);
void	check_args(int argc);
int		check_input(char *file_in);
void	clean_data(t_data *data);

#endif
