/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:52:54 by vjean             #+#    #+#             */
/*   Updated: 2023/02/07 11:41:18 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return NOTHING. Take t_cmd; the arguments following "echo" to be printed.
void	do_echo(t_cmd *cmd)
{
	int	newline;
	int	i;
	int	j;

	i = 1;
	newline = 1;
	if (cmd->cmd_args[i][0] == '-')
	{
		j = 1;
		while (cmd->cmd_args[i][j] == 'n')
			j++;
		if (cmd->cmd_args[i][j] == '\0')
		{
			newline = 0;
			i++;
		}
	}
	while (cmd->cmd_args[i])
	{
		if (2 < i || (1 < i && newline))
			printf(" ");
		printf("%s", cmd->cmd_args[i]);
		i++;
	}
	if (newline)
		printf("\n");
}