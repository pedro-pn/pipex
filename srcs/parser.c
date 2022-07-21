/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/21 11:22:04 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Get user inputs and format properly
char	**get_cmd(char *argv)
{
	char	**cmd;
	int		index_cmd;

	clean_quotes(argv);
	cmd = ft_split(argv, ' ');
	index_cmd = -1;
	while (index_cmd++, cmd[index_cmd])
		ft_memrpl(cmd[index_cmd], 1, 32, ft_strlen(cmd[index_cmd]));
	return (cmd);
}

void	clean_quotes(char *argv)
{
	int	index;
	int	flag;

	index = 0;
	flag = 1;
	while (argv[index])
	{
		if (argv[index] == 39)
		{
			argv[index] = 32;
			flag *= -1;
		}
		else if (flag == -1)
		{
			if (argv[index] == ' ')
				argv[index] = 1;
		}
		index++;
	}
}

int	get_path(t_data *data, char *cmd, char *envp[])
{
	char	**bin_paths;
	int		index;
	int		error;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp("PATH", envp[index], 4))
		{
			bin_paths = ft_split(envp[index], ':');
			break ;
		}
		index++;
	}
	error = check_path(data, bin_paths, cmd);
	clean_array(bin_paths);
	return (error);
}

int	check_path(t_data *data, char **bin_paths, char *cmd)
{
	int		index;
	char	*path;
	char	*temp;
	int		error;

	index = -1;
	while (index++, bin_paths[index])
	{
		temp = ft_strjoin(bin_paths[index], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			error = 0;
			break ;
		}
		else
			error = NOCMD;
		free(path);
		path = NULL;
	}
	data->path = path;
	return (error);
}

void	clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
