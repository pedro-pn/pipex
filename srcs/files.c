/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:28:24 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/21 12:47:21 by ppaulo-d         ###   ########.fr       */
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

int	get_output(char *file_out, int *pipe, int here_doc)
{
	unsigned char	buff[1];
	int				file_fd;
	int				b_read;

	if (here_doc == 1)
		file_fd = open(file_out, O_APPEND | O_WRONLY | O_CREAT, 0664);
	else
		file_fd = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_fd == -1)
	{
		ft_printf("%s: %s\n", file_out, strerror(errno));
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

void	get_user_input(t_data *data, char *delimiter)
{
	char	*buff;
	int		i;
	int		dlm_len;

	dlm_len = ft_strlen(delimiter);
	buff = ft_calloc(dlm_len + 1, sizeof(*buff));
	if (!buff)
		return ;
	while (read(STDIN_FILENO, buff, dlm_len))
	{
		i = 0;
		if (!ft_strncmp(buff, delimiter, dlm_len))
			break ;
		while (buff[i])
		{
			write(data->pipes[1][1], &buff[i], 1);
			i++;
		}
		ft_memset(buff, 0, dlm_len);
	}
	close(data->pipes[1][1]);
	free(buff);
}
