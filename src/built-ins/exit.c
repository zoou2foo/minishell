/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/01/27 15:39:14 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_cmd *cmd)
{
	long	arg;
	int		i;

	i = 0;
	while (cmd->cmd_args[1][i])
	{
		if (cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9') 
			i++;
		else if (!(cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9'))
			exit (255);
	}
	arg = ft_atol(cmd->cmd_args[1]);
	exit (arg);
}

// COMMENT It works! And TESTED.

/* What I put in the main to test it:
with adding specific stuff in the array:
		t_cmd	*cmd = ft_calloc(sizeof(t_cmd), 1);
		cmd->cmd_args = ft_calloc(sizeof(char *), 3);
		cmd->cmd_args[0] = "exit";
		cmd->cmd_args[1] = "45";
if (ft_strncmp(metadata->buf, "exit", 4) == 0)
				do_exit();

*/