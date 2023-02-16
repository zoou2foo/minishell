/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:33 by llord             #+#    #+#             */
/*   Updated: 2023/02/16 13:31:34 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->cmd_args && cmd->cmd_args[0])
		{
			i = -1;
			while (cmd->cmd_args[++i])
				ft_free_null(cmd->cmd_args[i]);
		}
		if (cmd->fdin > 0)
			close(cmd->fdin);
		if (cmd->fdout > 1)
			close(cmd->fdout);
	}
}

//frees a cmd_block, all its cmds, and all the leftover FDs
void	free_cmd_block(void)
{
	int		i;

	ft_free_null(g_meta->pid);
	if (g_meta->pipes)
	{
		i = -1;
		while (g_meta->pipes[++i])
		{
			if (g_meta->pipes[i][0] > 0)
				close(g_meta->pipes[i][0]);
			if (g_meta->pipes[i][1] > 0)
				close(g_meta->pipes[i][1]);
		}
		ft_free_null(g_meta->pipes);
	}
	if (g_meta->cmd_block)
	{
		i = -1;
		while (++i < g_meta->cmd_nb)
			free_cmd(g_meta->cmd_block[i]);
		ft_free_null(g_meta->cmd_block);
	}
}
