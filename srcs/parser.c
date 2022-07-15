/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/14 18:36:25 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_tokens	get_tokens(char *argv)
{
	t_tokens	tokens;
	char		*path;
	char		**cmds;
	char		*temp;

	path = "/usr/bin/";
	cmds = ft_split(argv, 32);
	temp = cmds[0];
	cmds[0] = ft_strjoin(path, temp);
	free(temp);
	tokens.cmd = cmds;
	return (tokens);
}
