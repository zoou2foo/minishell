/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:33 by llord             #+#    #+#             */
/*   Updated: 2023/02/21 15:36:31 by llord            ###   ########.fr       */
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

//frees a cmd_block, all its cmds, and all the leftover FDs
void	free_cmd_block(void)
{
	int	i;

	close_all();
	if (g_meta->pipes)
		ft_free_null(g_meta->pipes);
	if (g_meta->cmd_block)
	{
		i = -1;
		while (++i < g_meta->cmd_nb)
			free_cmd(g_meta->cmd_block[i]);
		ft_free_null(g_meta->cmd_block);
	}
}

//closes and frees everything from the g_meta
void	free_all(void)
{
	free_cmd_block();
	if (g_meta->buf)
		ft_free_null(g_meta->buf);
	if (g_meta->pid)
		ft_free_null(g_meta->pid);
	if (g_meta->env)
		ft_free_tab((void**)g_meta->env);
	if (g_meta->paths)
		ft_free_tab((void**)g_meta->paths);
}
