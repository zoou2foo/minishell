/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/24 12:48:40 by vjean            ###   ########.fr       */
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
//if WIFEXITED: if process exited normally
//if WIFSIGNALED: child exited on signal
//WTERMSIG: adds 128 when not needed (ex: cat kdjflkj)
void	waitchild(void)
{
	int	i;
	int	status_tmp;

	i = 0;
	status_tmp = 0;
	while (i < g_meta->cmd_nb)
	{
		waitpid(g_meta->pid[i], &status_tmp, 0);
		if (WIFEXITED(status_tmp) == TRUE)
			g_meta->exit_status = WEXITSTATUS(status_tmp);
		else if (WIFSIGNALED(status_tmp) == TRUE)
			g_meta->exit_status = 128 + WTERMSIG(status_tmp);
		else
			g_meta->exit_status = 128 + WSTOPSIG(status_tmp);
		i++;
	}
}

// Choose whether to execute a given cmd as a built_in or a sys_cmd
// Exits with an error if the execution failed
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
	throw_error(ERR_EXIT);
	free_cmd_block();
	exit(EXIT_FAILURE);
}

//take the cmd and the index to fork. Return int (exit)
int	try_fork(t_cmd *cmd, int i)
{
	init_signals(3);
	g_meta->pid[i] = cmd_fork();
	if (g_meta->pid[i] < 0)
	{
		fatal_error(MSTATE_F_ERR);
		return (EXIT_FAILURE);
	}
	if (g_meta->pid[i] == 0)
		child_process(cmd);
	if (0 < cmd->id)
		close(g_meta->pipes[cmd->id - 1][0]);
	if (cmd->id < g_meta->cmd_nb - 1)
		close(g_meta->pipes[cmd->id][1]);
	close_fds(cmd);
	return (EXIT_SUCCESS);
}

// Goes through the cmd_block and checks if the cmd is a built and if we need
//to fork(). Then either execute the cmd or passes it to a child process
void	execute_cmd_block(void)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	g_meta->exit_status = EXIT_SUCCESS;
	g_meta->pid = ft_calloc(sizeof(int), g_meta->cmd_nb);
	while (++i < g_meta->cmd_nb)
	{
		cmd = g_meta->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!built_ins_childable(cmd))
				execute_builtins(cmd);
			else if (cmd->argcount > 1 && is_same(cmd->cmd_args[0], "export"))
				execute_builtins(cmd);
			else if (try_fork(cmd, i))
				break ;
		}
		close_fds(cmd);
	}
	close_all();
	waitchild();
	init_signals(1);
	free_cmd_block();
}
