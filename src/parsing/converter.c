/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/27 08:57:46 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//merge tokens (ex > type + string = string w/ type >)
t_token	*merge_mergeables(t_token *node)
{
	while (node->next)
	{
		if (node->next->type > TTYPE_EXPAND && node->type > TTYPE_EXPAND)
		{
			if (g_meta->state == MSTATE_NORMAL)
			{
				throw_error(ERR_TOKEN);
				g_meta->state = MSTATE_O_REDIR;
				g_meta->exit_status = 2;
			}
		}
		if (node->next->type <= TTYPE_EXPAND && TTYPE_EXPAND < node->type)
			node = merge_tokens(node, node->next);
		if (node->next)
			node = node->next;
		else
			break ;
	}
	check_merge_error(node);
	return (find_head(node)); //reset head in case cut_token() destroys it
}

//finds redirection nodes and uses them
t_token	*get_redirs(t_token *node, t_cmd *cmd)
{
	while (node)
	{
		if (TTYPE_EXPAND < node->type)
		{
			get_redirs_in(node, cmd);
			get_redirs_out(node, cmd);
			if (has_fd_error(cmd))
				break ;
			node = cut_token(node); //removes node once processed
			if (!node->prev)
				continue ;
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (find_head(node)); //reset head in case cut_token() destroys it
}

//convert remaining tokens into cmd_args
t_cmd	*get_cmd_args(t_token *node, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (node)
	{
		if (node->type != TTYPE_EMPTY)
		{
			cmd->cmd_args[i++] = ft_strdup(node->string);
			cmd->argcount++;
		}
		node = node->next;
	}
	if (cmd->argcount > 0 && is_built_in(cmd->cmd_args[0]) == 1)
		cmd->is_built_in = true;
	return (cmd);
}

//convert a single token list into a cmd
t_cmd	*tokens_to_cmd(t_token **head, int id)
{
	t_cmd	*cmd;

	*head = merge_mergeables(*head);

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdin = 0;
	cmd->fdout = 1;
	cmd->id = id;

	*head = get_redirs(*head, cmd);

	cmd->cmd_args = ft_calloc(find_length(*head) + 1, sizeof(char *));
	return (get_cmd_args(*head, cmd));

}

//converts every token list into cmds
void	load_cmd_block(t_token **head)
{
	int	i;

	i = -1;
	if (g_meta->state != MSTATE_NORMAL)
		while (head && head[++i])
			free_token_list(head[i]);
	else
		while (g_meta->state == MSTATE_NORMAL && head && head[++i])
			g_meta->cmd_block[i] = tokens_to_cmd(&head[i], i); //assign to a temp to avoid hd issues with fds?
}

//une fois que tokens_to_cmd, temps de faire les check
// Check 1: cmd simple ou non(pipes)? ->Simple. Builtins ou sys_cmd? ->Builtins: execute. Sys_cmd fokr et execute.
// Pipes? ->call pipex_bonus