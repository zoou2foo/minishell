/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:22:25 by vjean             #+#    #+#             */
/*   Updated: 2023/02/20 09:41:32 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	execute_fork(t_cmd *cmd, int i)
{
	if (g_meta->pid[i] == 0)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		dup2(cmd->fdout, STDOUT_FILENO);
		child_process(cmd);
	}
}

void	close_n_execute(t_cmd *cmd)
{
	close_fds(cmd);
	execute_builtins(cmd);
}

void	fork_error(t_cmd *cmd)
{
	throw_error(ERR_FORK);
	g_meta->state = MSTATE_ERROR;
	g_meta->exit_status = EXIT_FAILURE;
	close_fds(cmd);
}
