/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 07:52:39 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Forks and check for fork() failure
int	cmd_fork(void)
{
	int	f_id;

	f_id = fork();
	if (f_id == -1)
	{
		fatal_error(MSTATE_F_ERR);
		return (-1);
	}
	if (f_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (f_id);
}

//status_tmp: add to avoid constantly rewriting on g_meta->exit_status
void	waitchildren(void)
{
	int	status_tmp;

	status_tmp = 0;
	waitpid(g_meta->pid, &status_tmp, 0); //WNOHANG; does not work when doing a sys_cmd ou built-ins tout seul (pas export; pas cd; pas unset; pas exit)
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
	//init_signals(E_SIG_CHLD);
	dup2(cmd->fdin, STDIN_FILENO);
	dup2(cmd->fdout, STDOUT_FILENO);
	close_all();
	if (cmd->is_built_in)
		execute_builtins(cmd); //if error use exit(EXIT_SUCCESS) in builtins. Mieux de ne pas les faire dans les enfants???
	else
	{
		exec_with_paths(cmd);
		free_cmd_block();
		exit(g_meta->exit_status); //this will set the value in the parent's g_meta->exit_status
	}
	//throw_error(ERR_EXIT);
	free_cmd_block();
	exit(EXIT_SUCCESS);
}

int	try_fork(t_cmd *cmd)
{
	//init_signals(E_SIG_CHLD); //on set avant child. besoin de reset aux signaux de depart. 
	g_meta->pid = cmd_fork();
	if (g_meta->pid < 0) //if fork error
	{
		fatal_error(MSTATE_F_ERR);
		return (EXIT_FAILURE);
	}
	if (g_meta->pid == 0)
		child_process(cmd);
	return (EXIT_SUCCESS);
}

void	launch_cmds()
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	while (++i < g_meta->cmd_nb)
	{
		cmd = g_meta->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!g_meta->must_fork && is_built_in(cmd->cmd_args[0]) && (!built_ins_childable(cmd) || (cmd->argcount > 1 && is_same(cmd->cmd_args[0], "export"))))
				execute_builtins(cmd);
			else if (try_fork(cmd))
				return ; //then close all childs and stuff
		}
	}
}

// Goes through the cmd_block and checks if the cmd is a built and if we need to fork()
void	execute_cmd_block(void)
{
	//init_signals(E_SIG_PRNT);
	g_meta->exit_status = EXIT_SUCCESS;
	if (g_meta->cmd_nb > 1)
		g_meta->must_fork = true;
	launch_cmds();
	//init_signals(E_SIG_PRNT);
	close_all();
	if (g_meta->must_fork)
	{
		sigignore(SIGINT);
		waitchildren();
	}
	free_cmd_block();
}
