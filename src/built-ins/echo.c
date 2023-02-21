/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:52:54 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 13:28:50 by vjean            ###   ########.fr       */
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

//close pipes at the very end. In a case, we had a leaks of pipe
void	close_pipes(void)
{
	int	i;

	i = 0;
	while (g_meta->pipes[i])
	{
		close(*g_meta->pipes[i]);
		i++;
	}
}

// Return NOTHING. Take t_cmd; the arguments following "echo" to be printed.
// important to close fds and pipes at the very end
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
	close_fds(cmd);
	close_pipes();
	exit(EXIT_SUCCESS);
}
