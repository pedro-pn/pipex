/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/20 10:47:03 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Get user inputs and format properly
char	**get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}

int	get_path(t_tokens *tokens, char *cmd, char *envp[])
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
	error = check_path(tokens, bin_paths, cmd);
	clean_array(bin_paths);
	return (error);
}

int	check_path(t_tokens *tokens, char **bin_paths, char *cmd)
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
	tokens->path = path;
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
