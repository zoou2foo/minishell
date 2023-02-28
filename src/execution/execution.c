/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 13:10:59 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//waits for the last child launched to finish and takes its exit status
void	waitchildren(void)
{
	int	status_tmp;

	status_tmp = 0;
	waitpid(g_meta->pid, &status_tmp, 0);
	if (WIFEXITED(status_tmp) == TRUE)
		g_meta->exit_status = WEXITSTATUS(status_tmp);
	else if (WIFSIGNALED(status_tmp) == TRUE)
		g_meta->exit_status = 128 + WTERMSIG(status_tmp);
	else
		g_meta->exit_status = 128 + WSTOPSIG(status_tmp);
}

//choses whether to execute a given cmd as a built_in or a sys_cmd
void	child_process(t_cmd *cmd)
{
	dup2(cmd->fdin, STDIN_FILENO);
	dup2(cmd->fdout, STDOUT_FILENO);
	close_all();
	if (cmd->is_built_in)
		execute_builtins(cmd);
	else
	{
		exec_with_paths(cmd);
		free_cmd_block();
		exit(g_meta->exit_status);
	}
	free_cmd_block();
	exit(EXIT_SUCCESS);
}

//attempts to fork() and calls child process if successful
int	try_fork(t_cmd *cmd)
{
	g_meta->pid = fork();
	if (g_meta->pid == -1)
	{
		fatal_error(MSTATE_F_ERR);
		return (-1);
	}
	if (g_meta->pid < 0)
	{
		fatal_error(MSTATE_F_ERR);
		return (EXIT_FAILURE);
	}
	if (g_meta->pid == 0)
		child_process(cmd);
	return (EXIT_SUCCESS);
}

//choses whether to execute a given cmd in the parent of in a child
void	launch_cmds(void)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	while (++i < g_meta->cmd_nb)
	{
		cmd = g_meta->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!g_meta->must_fork && is_built_in(cmd->cmd_args[0]) && (!is_childable(cmd)
					|| (cmd->argcount > 1 && is_same(cmd->cmd_args[0], "export", true))))
				execute_builtins(cmd);
			else if (try_fork(cmd))
				return ; //then close all childs ??
		}
	}
}

//setups things necessary to execute g_meta->cmd_block cmds properly
void	execute_cmd_block(void)
{
	g_meta->exit_status = EXIT_SUCCESS;
	g_meta->pid = 0;
	if (g_meta->cmd_nb > 1)
		g_meta->must_fork = true;
	signal(SIGINT, handler_child_sig);
	signal(SIGQUIT, handler_child_sig);
	launch_cmds();
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	close_all();
	if (g_meta->pid != 0)
		waitchildren();
	free_cmd_block();
}
