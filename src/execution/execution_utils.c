/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:22:25 by vjean             #+#    #+#             */
/*   Updated: 2023/02/22 13:14:08 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//closes the fdin and fdout of a given cmd
void	close_fds(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->fdin > 0)
			close(cmd->fdin);
		cmd->fdin = 0;
		if (cmd->fdout > 1)
			close(cmd->fdout);
		cmd->fdout = 1;
	}
}

//closes all pipes
void	close_pipes(void)
{
	int	i;

	i = -1;
	if (g_meta->pipes)
	{
		while (g_meta->pipes[++i])
		{
			close(g_meta->pipes[i][0]);
			close(g_meta->pipes[i][1]);
		}
	}
}

//closes all pipes and cmds fdin/fdout
void	close_all(void)
{
	int	i;

	i = -1;
	if (g_meta->cmd_block)
	{
		while (g_meta->cmd_block[++i])
			close_fds(g_meta->cmd_block[i]);
	}
	close_pipes();
}

//prints out out a specified error message
void	throw_error(char *str)
{
	write(2, str, ft_strlen(str));
}

//simplifies cmd name comparisons (compares only up to len(str) chars)
bool	is_same(char *arg, char *str)
{
	if (ft_strncmp(arg, str, ft_strlen(str)) == 0)
		return (true);
	return (false);
}
