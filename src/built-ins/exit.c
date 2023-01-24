/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2023/01/24 10:40:11 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_cmd *cmd) //Need to put back in void
{
	long	arg;
	int		i;

	i = 0;
	while (cmd->cmd_args[1][i]) // FIXME need to debug this part.
	{
		if (cmd->cmd_args[1][i] >= 48 && cmd->cmd_args[1][i] <= 57) 
			i++;
		else
			exit (0);
	}
	arg = ft_atol(cmd->cmd_args[1]);
	exit (arg);
}

// COMMENT It works! And TESTED. *** HOWEVER *** need to check if it got an
// COMMENT numeric argument like 42 or 32 or 1. Probably will need to add the
// COMMENT following to do the code:

/*
	need to do a function atol to check the following argument on exit. Do a loop
	to check if what is following is numeric. Then, pass the argument in atol
	That's what you will send in exit. --> exit (result_of_atol);
*/

/* What I put in the main to test it:
if (ft_strncmp(metadata->buf, "exit", 4) == 0)
				do_exit();

*/