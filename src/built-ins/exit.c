/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 12:58:55 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to check the args following exit; to shorten exit.
void	check_args_4_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[1][++i])
	{
		if ((i > 10 || (cmd->cmd_args[1][i] >= '0'
				&& cmd->cmd_args[1][i] <= '9')))
		{
			if (i != 0 || ((cmd->cmd_args[1][i] != '-')
				&& (cmd->cmd_args[1][i] != '+')))
			{
				throw_error(ERR_ARG2);
				exit (255);
			}
		}
	}
	return (ft_atoi(args[1]));
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
			check_args_4_exit(cmd);
			arg = ft_atoi(cmd->cmd_args[1]);
		}
		else
			arg = g_meta->exit_status;
		exit (arg);
	}
	throw_error(ERR_ARG3);
	exit (255);
}
