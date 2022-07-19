/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 15:29:18 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Get user inputs and format properly
char	**get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, 32);
	return (cmd);
}

int	get_path(t_tokens *tokens, char *cmd, char *envp[])
{
	char	*path;
	char	*env_path;
	char	**bin_paths;
	int		i;
	char	*temp;
	int		err;

	i = 0; // get paths
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			bin_paths = ft_split(envp[i], ':');
			break ;
		}
		i++;
	}
	//check paths
	i = 2;
	while (bin_paths[i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			err = 0;
			break ;
		}
		else
			err = 127;
		free(path);
		path = NULL;
		i++;
	}
	tokens->path = path;
	clean_array(bin_paths);
	//ft_printf("err: %d\n", err);
	return (err);
}

void	clean_array(char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}