/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:18:41 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/21 11:04:42 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

# define NOCMD 127
# define TRUE 1
# define FALSE 0

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

int		*get_pids(t_data data);
void	pipex_exec(t_data *data, char *argv[], char *envp[]);
void	exec_child(t_data *data, char *envp[], int process);
int		wait_processes(t_data *data, int processes_n);
// Parser functions

char	**get_cmd(t_data data, char *argv, int process);
int		get_path(t_data *data, char *cmd, char *envp[]);
int		check_path(t_data *data, char **bin_paths, char *cmd);
void	clean_quotes(char *argv);
void	clean_array(char **array);
// Pipes functions

int		**get_pipes(t_data data);
void	open_pipes(int **pipes);
void	close_child_pipes(int **pipes, int process);
void	close_main_pipes(int **pipes, int here_doc);
void	clean_pipes(int **pipes);
// i/o files functions

void	get_input(char *file_in, int *pipe);
void	get_user_input(t_data *data, char *delimiter);
int		get_output(char *file_out, int *pipe, int here_doc);

// error functions

void	check_args(int argc);
int		check_input(char *file_in);

#endif
