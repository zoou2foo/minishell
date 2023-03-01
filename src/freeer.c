/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:31:33 by llord             #+#    #+#             */
/*   Updated: 2023/03/01 09:45:52 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees a given cmd
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

//frees g_meta->pipes
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
//make sure to close beforehand
void	free_cmd_block(void)
{
	int	i;

	if (g_meta->cmd_block)
	{
		i = -1;
		while (++i < g_meta->cmd_nb)
			free_cmd(g_meta->cmd_block[i]);
		ft_free_null(g_meta->cmd_block);
		free_pipes();
	}
}

//frees everything from the g_meta
void	free_all(void)
{
	if (g_meta)
	{
		if (g_meta->env)
			ft_free_tab((void **)g_meta->env);
		if (g_meta->paths)
			ft_free_tab((void **)g_meta->paths);
	}
}

void	full_exit(int exit_status)
{
	clear_history();
	close_all();
	free_cmd_block();
	free_all();
	ft_free_null(g_meta);
	exit (exit_status);
}
