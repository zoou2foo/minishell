/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 13:12:57 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_args(char **args)
{
	int	i;

	i = -1;
	while (args[1][++i])
	{
		if ((i > 10 || !(args[1][i] >= '0'
				&& args[1][i] <= '9')))
		{
			if (i != 0 || ((args[1][i] != '-')
				&& (args[1][i] != '+')))
			{
				throw_error(ERR_ARG2);
				exit (255);
			}
		}
	}
}

// Return nothing. Take t_cmd. To look at the following argument to give the
// correct exit status.
//change for comparison with max string (?) 9223372036854775808; third if.
void	do_exit(t_cmd *cmd)
{
	unsigned char	arg;

	close_pipes();
	if (cmd->argcount < 3)
	{
		if (cmd->cmd_args[1])
		{
			check_exit_args(cmd->cmd_args);
			arg = ft_atoi(cmd->cmd_args[1]);
		}
		else
			arg = g_meta->exit_status;
		exit (arg);
	}
	throw_error(ERR_ARG3);
	exit (255);
}
