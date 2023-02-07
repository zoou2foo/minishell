/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/07 13:30:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use global var, so void. Fork and then deal with error.
void	cmd_fork(void)
{
	metadata->pid = fork();
	if (metadata->pid == -1)
	{
		//TODO : handle error
		write(2, ERR_PIPE, ft_strlen(ERR_PIPE));
		ft_free_null(metadata);
		exit (1);
	}
}

// Return nothing. Takes t_cmd to close all the fds.
void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != 1)
		close(cmd->fdout);
}

// Return nothing as in prep of execution of child process. Needs to take t_cmd
// to know the cmd and args the child takes care of.
// if is_built_in is false -> execute them; else execute sys_cmds with path
// then close everything and exit.
void	child_process(t_cmd *cmd)
{
	metadata->exit_status = 0;	//doesn't change the right exit status (duplicate metadata?) ????
								//should add exit 127 if cmd not found
	if (cmd->is_built_in == true)
	{
		execute_builtins(cmd);	//if error use exit(EXIT_SUCCESS) in builtins. Mieux de ne pas les faire dans les enfants???
		//TODO : handle error
		//write(STDERR_FILENO, "Command Error : Builtin failure\n", 33); //need to be moved
	}
	else
	{
		exec_with_paths(cmd);
		//TODO : handle error
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
	}
	close_fds(cmd);
	exit(EXIT_FAILURE);
}

// Main execution. Use global var. Return nothing.
// Going through the nb of cmds. Looking for exit to avoid doing it in child
// Then we fork.
void	execute_cmd_block(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;

	while (i < metadata->cmd_nb) //ajouter moins 1 ou non...
	{
		cmd = metadata->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!built_ins_childable(cmd))	//**handling exit() on its own to avoid childing Fonction pour check if childable
			{
				close_fds(cmd);
				execute_builtins(cmd);
			}
			else
			{
				cmd_fork();
				if (metadata->pid < 0)
				{
					write(2, ERR_PID, ft_strlen(ERR_PID));;
					//TODO : handle error
				}
				if (metadata->pid == 0)			//if child
				{
					dup2(cmd->fdin, STDIN_FILENO);
					dup2(cmd->fdout, STDOUT_FILENO);
					child_process(cmd);
				}
				init_signals(2);
				close_fds(cmd);
				waitpid(metadata->pid, &metadata->exit_status, 0);
				metadata->pid = 0;
			}
		}
		i++;
	}
	init_signals(1);
	//close all pipes ? si on a des leaks, soit placer dans le parent ou non
}
