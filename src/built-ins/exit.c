/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/02/03 09:46:42 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return nothing. Take t_cmd. To look at the following argument to give the
// correct exit status.
// ***NEED to be REVIEWED... still bug at times...***
void	do_exit(t_cmd *cmd)
{
	int	arg;		//needs to be a char? (0 to 255) modulo 256
	int	i;

	if (cmd->cmd_args[1])
	{
		i = 0;
		while (cmd->cmd_args[1][i])
		{
			if (cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9')
				i++;
			else if (!(cmd->cmd_args[1][i] >= '0' && cmd->cmd_args[1][i] <= '9'))
				exit (255);
		}
		arg = ft_atoi(cmd->cmd_args[1]) % 256;
	}
	else
		arg = 0;

	metadata->run = false;				//superfluous????

	exit (arg);
}
