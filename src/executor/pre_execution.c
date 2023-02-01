/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/01 15:04:23 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_fork(void)
{
	metadata->pid = fork();
	if (metadata->pid == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		ft_free_null(metadata);
		exit (1);
	}
}

void	child_process(t_cmd *cmd)
{
	metadata->cmd_path = find_cmd(cmd);
	//prêt à execve ici ou non??
	
}

void	execute_cmd_block(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;

	while (i < metadata->cmd_nb) //ajouter moins 1 ou non...
	{
		cmd = metadata->cmd_block[i];
	
		if (cmd->is_built_in)	//always falst for now : CHECK FOR BUILT IN IN LOAD_CMD_BLOCK
		{
			dup2(cmd->fdin, STDIN_FILENO);
			dup2(cmd->fdout, STDOUT_FILENO);
	
			//execute the built in

			if (cmd->fdin != 0)
				close(cmd->fdin);
			if (cmd->fdout != 1)
				close(cmd->fdout);
		}
		else
		{	
			cmd_fork();
		
			if (metadata->pid == 0)			//if child
			{
				dup2(cmd->fdin, STDIN_FILENO);
				dup2(cmd->fdout, STDOUT_FILENO);
				child_process(cmd);
			}
			else if (metadata->pid > 0)		//if parent		(close pipes in all cases)
			{
				if (cmd->fdin != 0)
					close(cmd->fdin);
				if (cmd->fdout != 1)
					close(cmd->fdout);
			}
			waitpid(metadata->pid, NULL, 0);
		}
		metadata->pid = 0;
		i++;
	}
	//close all pipes ? si on a des leaks, soit placer dans le parent ou non
}
