/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:52:54 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 19:58:55 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print arg; ft to shortent do_echo()
void	echo_print(t_cmd *cmd, int i, int newline)
{
	while (cmd->cmd_args[i])
	{
		if (2 < i || (1 < i && newline))
			printf(" ");
		printf("%s", cmd->cmd_args[i]);
		i++;
	}
}

// Return NOTHING. Take t_cmd; the arguments following "echo" to be printed.
void	do_echo(t_cmd *cmd)
{
	int	newline;
	int	i;
	int	j;

	i = 1;
	newline = 1;
	if (cmd->cmd_args[i] && cmd->cmd_args[i][0] == '-')
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
	echo_print(cmd, i, newline);
	if (newline)
		printf("\n");
	close_fds(cmd); //maybe need to close fds in 
	exit(EXIT_SUCCESS);
}
