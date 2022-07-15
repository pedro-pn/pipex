/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:30:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/15 12:20:12 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define PROCESS 3

int	main(int argc, char *argv[])
{
	char	*file1;
	char	*file2;
	int		pipe_fd[PROCESS + 1][2];
	int		pids[PROCESS];
	int		file_fd;
	int 	i;
	int		j;
	int		k;

	
	t_tokens	tokens;
	file1 = argv[1];
	file2 = argv[argc]; // Child escreve nesse - Main Lê
	char	buff[1];
	i = 0;
	while (i < PROCESS + 1)
	{
		pipe(pipe_fd[i]);
		i++;
	}
	i = 0;
	while (i < PROCESS)
	{
		pids[i] = fork();
	
		if (pids[i] == 0)
		{
			k = 0;
			while (k < PROCESS + 1)
			{
				if (k != i)
					close(pipe_fd[k][0]);
				if (k != i + 1)
					close(pipe_fd[k][1]);
				k++;
			}
			tokens = get_tokens(argv[i + 2]);
		//	ft_printf("%s\n", tokens.cmd[1]);
			dup2(pipe_fd[i][0], 0);
			dup2(pipe_fd[i + 1][1], 1);
			close(pipe_fd[i][0]);
			close(pipe_fd[i + 1][1]);
			execve(tokens.cmd[0], tokens.cmd, NULL);
		}
		i++;
	}
	int x;
	char	str[200];
	//char	info[80] = "Eu sou Pedro\nPedro chapeu\nO supremo\nGatinhos são legais\ngente chata vai a merda";
	x = 0;

	while (x < PROCESS + 1)
	{
		if (x != PROCESS)
			close(pipe_fd[x][0]);
		if (x != 0)
			close(pipe_fd[x][1]);
		x++;
	}
	// This is working \/
	file_fd = open(file1, O_RDONLY);
	while (read(file_fd, buff, sizeof(char)) > 0)
		write(pipe_fd[0][1], buff, sizeof(char));
		
	close(file_fd);
	close(pipe_fd[0][1]);

	i = 0;
	while (read(pipe_fd[PROCESS][0], &buff, sizeof(char)) > 0)
	{
		str[i] = *buff;
		i++;
	}
	ft_printf("%s", str);
	close(pipe_fd[PROCESS][0]);
	j = 0;
	while (j < PROCESS)
	{
		wait(NULL);
		j++;
	}

	return 0;



	// char buff[1];

	// char buffer[1];
	// char y[250];
	// int i;
	// close(pipe_1[1]);
	// close(pipe_2[0]);
	// close(pipe_2[1]);
	// i = 0;
	// while (read(pipe_1[0], &buffer, sizeof(char)) > 0)
	// {
	// 	y[i] = *buffer;
	// 	i++;
	// }
	// ft_printf("%s", y);
	// return 0;
}