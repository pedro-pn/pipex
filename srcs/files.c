/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:28:24 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 17:04:10 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_input(char *file_in, int *pipe)
{
	int	file_fd;

	file_fd = open(file_in, O_RDONLY);
	if (file_fd == -1)
	{
		dup2(pipe[0], 0);
		close(pipe[1]);
		return ;
	}
	dup2(file_fd, 0);
	close(file_fd);
	close(pipe[1]);
}

int	get_output(char *file_out, int *pipe)
{
	unsigned char	buff[1];
	int				file_fd;
	int				b_read;

	file_fd = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_fd == -1)
	{
		ft_printf("bash: %s: %s\n", file_out, strerror(errno));
		close(pipe[0]);
		return (-1);
	}
	b_read = read(pipe[0], buff, sizeof(buff));
	while (b_read > 0)
	{
		write(file_fd, buff, sizeof(buff));
		b_read = read(pipe[0], buff, sizeof(buff));
	}
	close(file_fd);
	close(pipe[0]);
	return (0);
}
