/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/17 20:36:04 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Get user inputs and format properly
char	**get_cmd(char *argv)
{
	char	*path;
	char	**cmd;
	char	*temp;

	path = "/usr/bin/";
	cmd = ft_split(argv, 32);
	temp = cmd[0];
	cmd[0] = ft_strjoin(path, temp);
	free(temp);
	return (cmd);
}
