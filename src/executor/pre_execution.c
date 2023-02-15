/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 10:20:55 by llord            ###   ########.fr       */
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
		//TODO : handle error
		throw_error(ERR_PIPE);
		ft_free_null(g_meta);
	}
	if (f_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (f_id);
}

// Closes the fdin and fdout of a given cmd
void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != 0)
		close(cmd->fdin);
	cmd->fdin = 0;
	if (cmd->fdout != 1)
		close(cmd->fdout);
	cmd->fdout = 1;
}

// Choses whether to execute a given cmd as a built_in or a sys_cmd
// Exits with an error if the execution failed
void	child_process(t_cmd *cmd)
{
	if (cmd->is_built_in)
	{
		execute_builtins(cmd);	//if error use exit(EXIT_SUCCESS) in builtins. Mieux de ne pas les faire dans les enfants???
		close_fds(cmd);
		//built_ins should have exited themselves
		//TODO : handle error
	}
	else
	{
		exec_with_paths(cmd);
		close_fds(cmd);
		exit(g_meta->exit_status);	//this will set the value in the parent's g_meta->exit_status
		//TODO : handle error
	}
	//safety exit (FOR DEBUGGING)
	throw_error(ERR_EXIT);
	exit(1);
}

// Goes through the cmd_block and checks if the cmd is a built and if we need to fork()
// Then either execute the cmd or passes it to a child process
void	execute_cmd_block(void)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	g_meta->exit_status = EXIT_SUCCESS; //sets success as default case
	g_meta->pid = ft_calloc(sizeof(int), g_meta->cmd_nb);
	while (++i < g_meta->cmd_nb)
	{
		cmd = g_meta->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!built_ins_childable(cmd)) //calls non-childable functions directly
			{
				close_fds(cmd);
				execute_builtins(cmd);
			}
			else if (cmd->argcount > 1 && is_same(cmd->cmd_args[0], "export")) //calls export directly IF its has args
			{
				close_fds(cmd);
				execute_builtins(cmd);
			}
			else
			{
				g_meta->pid[i] = cmd_fork();
				if (g_meta->pid[i] < 0) //if fork error
				{
					throw_error(ERR_PID);
					g_meta->state = MSTATE_ERROR;
					//TODO : handle error
				}
				if (g_meta->pid[i] == 0) //if is child
				{
					signal(SIGINT, SIG_DFL);
					dup2(cmd->fdin, STDIN_FILENO);
					dup2(cmd->fdout, STDOUT_FILENO);
					child_process(cmd);
				}
				close_fds(cmd);
				waitchild();
			}
		}
	}
	ft_free_null(g_meta->pid);
	init_signals(1);
}

void	setup_exit_code(int sig)
{
	g_meta->exit_status = sig;
}

void	waitchild(void)
{
	int	i;
	int	status_tmp; //add to avoid constantly rewriting on g_meta->exit_status

	i = 0;
	status_tmp = 0;
	while (i < g_meta->cmd_nb)
	{
		waitpid(g_meta->pid[i], &status_tmp, 0);
		if (WIFEXITED(status_tmp) == TRUE) //if process exited normally
			setup_exit_code(WEXITSTATUS(status_tmp));
		else if (WIFSIGNALED(status_tmp) == TRUE) //child exited on signal
			setup_exit_code(WTERMSIG(status_tmp) + 128);	//adds 128 when not needed (ex: cat sdglhskjgkjs)
		else
			setup_exit_code(128 + WSTOPSIG(status_tmp));
		i++;
	}

}
