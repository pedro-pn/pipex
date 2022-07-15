/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:28:24 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/15 15:58:48 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_input(char *file_in, int *pipe)
{
	int		file_fd;
	int		b_read;
	char	buff[1];

	file_fd = open(file_in, O_RDONLY);
	b_read = read(file_fd, buff, sizeof(char));
	while (b_read > 0)
	{
		write(pipe[1], buff, sizeof(char));
		b_read = read(file_fd, buff, sizeof(char));
	}
	close(file_fd);
	close(pipe[1]);
}

void	get_output(char *file_out, int *pipe)
{
	char	buff[1];
	int		file_fd;
	int		b_read;

	file_fd = open(file_out, O_RDWR | O_CREAT, 0664);
	b_read = read(pipe[0], buff, sizeof(char));
	while (b_read > 0)
	{
		write(file_fd, buff, sizeof(char));
		b_read = read(pipe[0], buff, sizeof(char));
	}
	close(file_fd);
	close(pipe[0]);
	
}