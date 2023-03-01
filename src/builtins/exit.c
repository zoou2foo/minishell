/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:46:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//makes sure the given arg is usable
void	check_exit_args(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if ((i > 10 || !(arg[i] >= '0'
					&& arg[i] <= '9')))
		{
			if (i != 0 || ((arg[i] != '-')
					&& (arg[i] != '+')))
			{
				throw_error(ERR_ARG2);
				full_exit(255);
			}
		}
	}
}

//tries to exit based on the given cmd->args[1] arg
void	do_exit(t_cmd *cmd)
{
	unsigned char	arg;

	close_all();
	if (cmd->argcount < 3)
	{
		if (cmd->cmd_args[1])
		{
			check_exit_args(cmd->cmd_args[1]);
			arg = ft_atoi(cmd->cmd_args[1]);
		}
		else
			arg = g_meta->exit_status;
		full_exit(arg);
	}
	full_exit(255);
}
