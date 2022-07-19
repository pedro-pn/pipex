/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/19 13:58:05 by ppaulo-d         ###   ########.fr       */
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

char	*get_path(char	*cmd)
{
	char	*path;

	path = ft_strjoin("/usr/bin/", cmd);
	return (path);
}
