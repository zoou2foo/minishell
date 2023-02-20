/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/20 14:48:06 by llord            ###   ########.fr       */
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
	cmd->fdin = 0;		//set default fd to use later
	cmd->fdout = 1;		//set default fd to use later
	cmd->id = id;		//sets the id of the

	*head = get_redirs(*head, cmd);

	//use pipes fds if fdin/fdout have not been set
	if (cmd->fdin == 0 && 0 < id)
		cmd->fdin = g_meta->pipes[id - 1][0];
	if (cmd->fdout == 1 && id < g_meta->cmd_nb - 1)
		cmd->fdout = g_meta->pipes[id][1];

	cmd->cmd_args = ft_calloc(find_length(*head) + 1, sizeof(char *));

	return (get_cmd_args(*head, cmd));

}

//converts every token list into cmds
void	load_cmd_block(t_token **head)
{
	int	i;

	if (g_meta->state == MSTATE_NORMAL)
	{
		g_meta->cmd_block = ft_calloc(g_meta->cmd_nb + 1, sizeof(t_cmd *));
		g_meta->pipes = ft_calloc(g_meta->cmd_nb, sizeof(int *));

		i = -1;
		while (++i < g_meta->cmd_nb - 1) //creates potentially needed pipes
		{
			g_meta->pipes[i] = ft_calloc(2, sizeof(int));
			pipe(g_meta->pipes[i]);
			//check for pipe errors here
		}

		//actual token conversion loop
		i = -1;
		while (head[++i])
			g_meta->cmd_block[i] = tokens_to_cmd(&head[i], i);
	}
}
