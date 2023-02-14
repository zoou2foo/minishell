/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/14 10:57:14 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return nothing. Take t_cmd. To look at the following argument to give the
// correct exit status.
void	do_exit(t_cmd *cmd)
{
	int	arg;
	int	i;

	if (cmd->cmd_args[1])
	{
		i = 0;
		while (cmd->cmd_args[1][i])
		{
			if (cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9')
				i++;
			else if (!(cmd->cmd_args[1][i] >= '0'
				&& cmd->cmd_args[1][i] <= '9'))
				exit (255);
		}

		arg = ft_atoi(cmd->cmd_args[1]); //+10 ou -10?? exit +10; exit -10;
		if (arg > 255 || arg < 0)
			arg = 255;
	}
	else
		arg = 0;
	exit (arg);
}
