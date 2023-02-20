/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/20 11:24:19 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_on_args(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if ((args[1][i] >= '0' && args[1][i] <= '9')
			|| (args[1][0] == '-' && i == 0)
			|| (args[1][0] == '+' && i == 0))
			i++;
		else if (!(args[1][i] >= '0' && args[1][i] <= '9'))
			exit (255);
	}
	return (ft_atoi(args[1]));
}

// Return nothing. Take t_cmd. To look at the following argument to give the
// correct exit status.
//change for comparison with max string (?) 9223372036854775808; third if.
void	do_exit(t_cmd *cmd)
{
	unsigned char	arg;

	arg = 255;
	if (cmd->argcount < 3)
	{
		if (cmd->cmd_args[1])
		{
			if (ft_strlen(cmd->cmd_args[1]) <= 10) //change for comparison with max string (?) 9223372036854775808
				arg = loop_on_args(cmd->cmd_args);
			else
				throw_error(ERR_ARG2);
		}
		else
			arg = g_meta->exit_status;
		exit (arg);
	}
	throw_error(ERR_ARG3);
	close_pipes();
	exit (arg);
}
