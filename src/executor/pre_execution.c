/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/01/30 09:47:36 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(void)
{
	t_token	**head;

	head = parse_line(metadata->buf);
	tokens_to_cmd(head);
	fill_path_tab();
	/*
	while (index < nombre_de_cmds)
	{
		pipe_n_fork();
		if (pid > 0)
		{
			dup2(fdout[0], STDIN);
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
	execute_child();
}




*/