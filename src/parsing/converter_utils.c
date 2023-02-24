/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/24 10:11:02 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_merge_error(t_token *node)
{
	if (node->type > TTYPE_EXPAND && !node->string[0])
	{
		if (g_meta->state == MSTATE_NORMAL)
		{
			throw_error(ERR_TOKEN);
			g_meta->state = MSTATE_O_REDIR;
			g_meta->exit_status = 2;
		}
	}
}

//deals with > and >> tokens
void	get_redirs_in(t_token *node, t_cmd *cmd)
{
	if (node->type == TTYPE_S_RDR_OUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		cmd->fdout = open(node->string, O_CREAT | O_RDWR | O_TRUNC, 0666);
	}
	else if (node->type == TTYPE_D_RDR_OUT)
	{
		if (cmd->fdout != 1)
			close(cmd->fdout);
		cmd->fdout = open(node->string, O_CREAT | O_RDWR | O_APPEND, 0666);
	}
}

//deals with < and << tokens
void	get_redirs_out(t_token *node, t_cmd *cmd)
{
	if (node->type == TTYPE_REDIR_IN)
	{
		if (cmd->fdin != 0)
			close(cmd->fdin);
		cmd->fdin = open(node->string, O_RDONLY);
	}
	else if (node->type == TTYPE_HEREDOC)
	{
		if (cmd->fdin != 0)
			close(cmd->fdin);
		if (g_meta->state == MSTATE_NORMAL)
			cmd->fdin = execute_hd(node->string);
		else
			cmd->fdin = 0;
	}
}

//checks for open() errors (fd = -1)
bool	has_fd_error(t_cmd *cmd)
{
	if (cmd->fdin < 0 || cmd->fdout < 0)
	{
		if (g_meta->state == MSTATE_NORMAL)
		{
			throw_error(ERR_FILE);
			g_meta->state = MSTATE_BAD_FD;
			g_meta->exit_status = EXIT_FAILURE;
		}
		return (true);
	}
	return (false);
}
