/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:22:25 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 13:47:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Closes the fdin and fdout of a given cmd
void	close_fds(t_cmd *cmd)
{
	if (cmd->fdin != 0)
		close(cmd->fdin);
	cmd->fdin = 0;
	if (cmd->fdout != 1)
		close(cmd->fdout);
	cmd->fdout = 1;
}

//throws out a specified error message
void	throw_error(char *str)
{
	write(2, str, ft_strlen(str));
}

//simplifies cmd name comparisons (compares only up to len(str) chars)
bool	is_same(char *arg, char *str)
{
	if (ft_strncmp(arg, str, ft_strlen(str)) == 0)
		return (true);
	return (false);
}
