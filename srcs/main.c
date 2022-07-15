/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/14 23:16:33 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	char	*file1;
	char	*file2;
	int		pipe_1[2];
	int		pipe_2[2];
	int		pid;
	int		file_fd;
	int		i_arg;
	
	t_tokens	tokens;
	file1 = argv[1];
	file2 = argv[argc];
	file_fd = open(file1, O_RDONLY);
	pipe(pipe_1); // Child escreve nesse - Main Lê
	pipe(pipe_2); // Main escreve nesse - Child lê
	i_arg = 2;
	//dup2(file_fd, pipe_2[0]);
	//close(file_fd);
	char buff[1];
	while (i_arg < argc - 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i_arg == 2)
			{
				dup2(file_fd, pipe_2[0]);
				close(file_fd);
			}
			tokens = get_tokens(argv[i_arg]);
		//	ft_printf("oi\n");
		//	ft_printf("%s\n", tokens.cmd[1]);
			// close(pipe_1[0]);
			// close(pipe_2[1]);
		//	ft_printf("oi\n");
			dup2(pipe_2[0], 0);
			dup2(pipe_1[1], 1);
			close(pipe_1[1]);
			close(pipe_2[0]);
			close(pipe_2[1]);
			close(pipe_1[0]);
			//ft_printf("oi\n");
			execve((tokens.cmd)[0], tokens.cmd, NULL); // escreveu no pipe
		}
		wait(NULL);
	//	dup2(pipe_1[0], pipe_2[1]);
		 close(pipe_1[1]);
		 close(file_fd);
		//close(pipe_2[0]);
	//	if (i_arg == argc - 2)
		// while (read(pipe_1[0], &buff, sizeof(char)) > 0)
		// {
		// 	ft_printf("bytes wrote: %d\t char: %s\n", write(pipe_2[1], &buff, sizeof(char)), buff);
		// }
		//close(file_fd);
	//	char b[2];
		
		// read(pipe_1[0], &b, 1);
		// ft_printf("%s\n", b);
	///	ft_printf("oi\n");
		i_arg++;
	}
	// while (wait(NULL) != -1 || errno != ECHILD)
	// 	ft_printf("waiting");
	char buffer[1];
	char y[250];
	int i;
	close(pipe_1[1]);
	close(pipe_2[0]);
	close(pipe_2[1]);
	i = 0;
	while (read(pipe_1[0], &buffer, sizeof(char)) > 0)
	{
		y[i] = *buffer;
		i++;
	}
	ft_printf("%s", y);
	return 0;
}