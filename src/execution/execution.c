/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 15:29:37 by llord            ###   ########.fr       */
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

// Choses whether to execute a given cmd as a built_in or a sys_cmd
// Exits with an error if the execution failed
// else: this will set the value in the parent's g_meta->exit_status
void	child_process(t_cmd *cmd)
{
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
	throw_error(ERR_EXIT);
	free_cmd_block();
	exit(EXIT_FAILURE);
}

int	try_fork(t_cmd *cmd, int i)
{
	g_meta->pid[i] = cmd_fork();
	init_signals(3);
	if (g_meta->pid[i] < 0) //if fork error
	{
		fatal_error(MSTATE_F_ERR);
		return (EXIT_FAILURE);
	}
	if (g_meta->pid[i] == 0)
		child_process(cmd);
	close_fds(cmd);
	waitchild();
	return (EXIT_SUCCESS);
}

// Goes through the cmd_block and checks if the cmd is a built and if we need
//to fork()
//g_meta->exit_status at beginning set to EXIT_SUCCESS as default
// Then either execute the cmd or passes it to a child process
//if => //calls non-childable functions directly
//else if => calls export directly IF its has args
//pid[i] == 0 => if is child
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
			if (!built_ins_childable(cmd)) //calls non-childable functions directly
				execute_builtins(cmd);
			else if (cmd->argcount > 1 && is_same(cmd->cmd_args[0], "export"))
				execute_builtins(cmd);
			else if (try_fork(cmd, i))
				break ;
		}
	}
	init_signals(1);
}
