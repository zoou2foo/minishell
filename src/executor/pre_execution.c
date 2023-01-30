/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/01/30 16:47:25 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(void)
{
	t_token	**head;

	head = parse_line(metadata->buf);
	fill_path_tab();
	/*
	while (index < nombre_de_cmds) utiliser t_cmd cmd_block (meta)
	{
		pipe_n_fork();
		if (pid > 0)
		{
			dup2(fdout[0], STDIN); //dup2(pipes[id - 1][1], STDIN) 
			close(fdout[0]);
			close(fdout[1]);
		}
		else if (pid == 0)
			child_process()
		index++;
	}
	close_fd_n_wait
	*/
}

/*
void	pipe_n_fork()
	pipe();
	fork();


void	child_process()
{
	int	index;

	t_cmd *cmd_path;
	cmd_path = find_cmd;
	execute_child(); --> now, real execution. Create a file for it.
}




*/