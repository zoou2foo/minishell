/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:10:13 by vjean             #+#    #+#             */
/*   Updated: 2023/02/27 11:05:32 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitchild(void)
{
	int	i;
	int	status_tmp;

	i = 0;
	status_tmp = 0;
	while (i < g_meta->cmd_nb)
	{
		waitpid(*g_meta->pid, &status_tmp, 0);
		if (WIFEXITED(status_tmp) == TRUE)
			g_meta->exit_status = WEXITSTATUS(status_tmp);
		else if (WIFSIGNALED(status_tmp) == TRUE)
			g_meta->exit_status = 128 + WTERMSIG(status_tmp);
		else
			g_meta->exit_status = 128 + WSTOPSIG(status_tmp);
		i++;
	}
}

void	close_n_wait(void)
{
	close(*g_meta->pipes[0]);
	close(*g_meta->pipes[1]);
	waitchild();
}

void	child_process(t_cmd *cmd)
{
	dup2(cmd->fdin, STDIN_FILENO);
	dup2(cmd->fdout, STDOUT_FILENO); //close all right after ou attendre plus loin
	if (cmd->is_built_in) //est-ce qu'on skip ou pas? besoin de le faire ou non? car on est dans pipe
		execute_builtins(cmd); //peut-etre pas besoin et peut-etre besoin d'ajouter exit status pour passer au parent? le setup a zero ou non???
	else
	{
		exec_with_paths(cmd);
		free_cmd_block();
		exit(g_meta->exit_status); //pour passer l'exit au parent...
	}
	close_all(); //check s'il faut mettre avant if ou enlever tout court
}

void	pipex(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = g_meta->cmd_block[i];
	if (g_meta->cmd_nb == 1) //si cmd simple
	{
		if (is_built_in(cmd->cmd_args[0]))
			execute_builtins(cmd);
		else
			exec_with_paths(cmd); //should add fork...
	}
	else if (g_meta->cmd_nb > 1) // plusieurs cmds avec pipes
	{
		while (i < g_meta->cmd_nb)
		{
			if (pipe(*g_meta->pipes) == -1)
			{
				//message error
				free_cmd_block();
				g_meta->exit_status = EXIT_FAILURE;
			}
			g_meta->pid[i] = fork();
			if (g_meta->pid[i] == -1)
			{
				//error message
				free_all(); //need to check if pipes close
				g_meta->exit_status = EXIT_FAILURE;
			}
			if (g_meta->pid[i] > 0) //parent
			{
				dup2(*g_meta->pipes[0], STDIN_FILENO);
				close(*g_meta->pipes[0]);
				close(*g_meta->pipes[1]);
			}
			else if (g_meta->pid[i] == 0) //child
				child_process(cmd);
			i++;
		}
	}
	close_n_wait();
}