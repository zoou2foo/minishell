/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:33 by llord             #+#    #+#             */
/*   Updated: 2023/02/24 10:57:33 by vjean            ###   ########.fr       */
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
		close_fds(cmd);
	}
}

void	free_pipes(void)
{
	int	i;

	if (g_meta->pipes)
	{
		i = -1;
		while (g_meta->pipes[++i])
			ft_free_null(g_meta->pipes[i]);
		ft_free_null(g_meta->pipes);
	}
}

//frees a cmd_block, all its cmds, and all the leftover FDs
void	free_cmd_block(void)
{
	int	i;

	if (g_meta->cmd_block)
	{
		free_pipes();
		i = -1;
		while (++i < g_meta->cmd_nb)
			free_cmd(g_meta->cmd_block[i]);
		ft_free_null(g_meta->cmd_block);
	}
}

//closes and frees everything from the g_meta
void	free_all(void)
{
	if (g_meta)
	{
		if (g_meta->pid)
			ft_free_null(g_meta->pid);
		if (g_meta->env)
			ft_free_tab((void **)g_meta->env);
		if (g_meta->paths)
			ft_free_tab((void **)g_meta->paths);
	}
}
