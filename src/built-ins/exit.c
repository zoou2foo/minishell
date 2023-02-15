/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 13:29:07 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return nothing. Take t_cmd. To look at the following argument to give the
// correct exit status.
void	do_exit(t_cmd *cmd)
{
	unsigned char	arg;
	int				i;

	if (cmd->cmd_args[1])
	{
		i = 0;
		while (cmd->cmd_args[1][i])
		{
			if ((cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9')
				|| (cmd->cmd_args[1][0] == '-' && i == 0))
				i++;
			else if (!(cmd->cmd_args[1][i] >= '0'
				&& cmd->cmd_args[1][i] <= '9'))
				exit (255);
		}
		arg = ft_atoi(cmd->cmd_args[1]);
	}
	else
		arg = g_meta->exit_status;
	exit (arg);
}
