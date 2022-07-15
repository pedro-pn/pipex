/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/07/15 16:46:15 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Get user inputs and format properly
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

// get total number of process (number of bash commands)
void	get_processesnum(t_tokens *tokens, int argc)
{
	tokens->processes_n = argc - 3;
}

int	*get_pids(t_tokens tokens)
{
	int	*pids;

	pids = malloc(sizeof(*pids) * tokens.processes_n);
	return (pids);
}
