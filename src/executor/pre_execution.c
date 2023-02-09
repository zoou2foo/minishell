/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 11:17:50 by vjean            ###   ########.fr       */
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
		ft_free_null(metadata);
	}
	return (f_id);
}

// Closes the fdin and fdout of a given cmd
void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != 1)
		close(cmd->fdout);
}

// Choses wheter to execute a given cmd as a built_in or a sys_cmd
// Exits with an error if the execution failed
void	child_process(t_cmd *cmd)
{
	if (cmd->is_built_in == true)
	{
		execute_builtins(cmd);	//if error use exit(EXIT_SUCCESS) in builtins. Mieux de ne pas les faire dans les enfants???
		//TODO : handle error
	}
	else
	{
		exec_with_paths(cmd);
		//TODO : handle error
	}
	close_fds(cmd);
	exit(EXIT_FAILURE);		//this will set the value in the parent's metadata->exit_status
}

// Goes through the cmd_block and checks if the cmd is a built and if we need to fork()
// Then either execute the cmd or passes it to a child process
void	execute_cmd_block(void)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	metadata->pid = ft_calloc(sizeof(int), metadata->cmd_nb);
	while (++i < metadata->cmd_nb)
	{
		cmd = metadata->cmd_block[i];
		if (cmd->argcount > 0)
		{
			if (!built_ins_childable(cmd))	//calls non-childable functions directly
			{
				close_fds(cmd);
				execute_builtins(cmd);
			}
			else if (cmd->argcount > 1 && ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
			{								//calls export directly IF its has args
				close_fds(cmd);
				execute_builtins(cmd);
			}
			else
			{
				metadata->pid[i] = cmd_fork();
				if (metadata->pid[i] < 0)
				{
					throw_error(ERR_PID);
					//TODO : handle error
				}
				if (metadata->pid[i] == 0)			//if child
				{
					dup2(cmd->fdin, STDIN_FILENO);
					dup2(cmd->fdout, STDOUT_FILENO);
					child_process(cmd);
				}
				init_signals(2);
				close_fds(cmd);
				//waitpid(metadata->pid, &metadata->exit_status, 0);
				// metadata->pid = 0;
			}
		}
	}
	waitchild();
	init_signals(1);
	//free the cmd_block and its t_cmds here
	//free (and close?) the pipe array here
}


void waitchild()
{
	int i;

	i = 0;
	while (i < metadata->cmd_nb)
	{
		waitpid(metadata->pid[i], &metadata->exit_status, 0);
		if (WIFEXITED(metadata->exit_status) == TRUE)
			metadata->exit_status = WEXITSTATUS(metadata->exit_status);
		i++;
	}
}
