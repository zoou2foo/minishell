/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/16 13:32:43 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert a single token list into a cmd, setting all info needed for execution
t_cmd	*tokens_to_cmd(t_token **head, int id)				// SPLIT ME UP SMH
{
	t_token	*node;
	int		i;
	t_cmd	*cmd;

	node = *head;
	while (node->next) //merge tokens (ex > type + string = string w/ type >)
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
	if (node->type > TTYPE_EXPAND && !node->string[0])
	{
		if (g_meta->state == MSTATE_NORMAL)
		{
			throw_error(ERR_TOKEN);
			g_meta->state = MSTATE_O_REDIR;
			g_meta->exit_status = 2;
		}
	}

	//reset head in case cut_token() destroys it
	*head = find_head(node);
	node = *head;

	//print_token_list(*head, true);				//DEBUG

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->fdin = 0;		//set default fd to use later
	cmd->fdout = 1;		//set default fd to use later
	cmd->id = id;		//sets the id of the

	//finds redirection nodes and uses them
	while (node)
	{
		if (TTYPE_EXPAND < node->type)
		{
			if (node->type == TTYPE_S_RDR_OUT) //		>
			{
				if (cmd->fdout != 1)
					close(cmd->fdout);
				cmd->fdout = open(node->string, O_CREAT | O_RDWR | O_TRUNC, 0666);
			}
			else if (node->type == TTYPE_D_RDR_OUT) //	>>
			{
				if (cmd->fdout != 1)
					close(cmd->fdout);
				cmd->fdout = open(node->string, O_CREAT | O_RDWR | O_APPEND, 0666);
			}
			else if (node->type == TTYPE_REDIR_IN) //	<
			{
				if (cmd->fdin != 0)
					close(cmd->fdin);
				cmd->fdin = open(node->string, O_RDONLY);
			}
			else if (node->type == TTYPE_HEREDOC) //	<<
			{
				if (cmd->fdin != 0)
					close(cmd->fdin);
				if (g_meta->state == MSTATE_NORMAL) //prevent calling hd when error has occured
					cmd->fdin = execute_hd(node->string);
				else
					cmd->fdin = 0;
			}
			//checks for open() errors (fd = -1)
			if (cmd->fdin < 0 || cmd->fdout < 0)
			{
				if (g_meta->state == MSTATE_NORMAL)
				{
					throw_error(ERR_FILE);
					g_meta->state = MSTATE_BAD_FD;
					g_meta->exit_status = EXIT_FAILURE;
				}
				break ;
			}
			//removes node once processed
			node = cut_token(node);
			if (!node->prev)
				continue ;
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}

	//uses the piepes if no fdin/fdout set
	if (cmd->fdin == 0 && 0 < id)
		cmd->fdin = g_meta->pipes[id - 1][0];
	if (cmd->fdout == 1 && id < g_meta->cmd_nb - 1)
		cmd->fdout = g_meta->pipes[id][1];

	//reset head in case cut_token() destroys it
	*head = find_head(node);
	node = *head;

	//print_token_list(*head, false);										//DEBUG

	cmd->cmd_args = ft_calloc(find_length(node) + 1, sizeof(char *));

	i = 0;
	//convert remaining tokens into cmd_args
	while (node)
	{
		if (node->type != TTYPE_EMPTY)
		{
			cmd->cmd_args[i++] = ft_strdup(node->string);
			cmd->argcount++;
		}
		node = node->next;
	}

	//activates is_built_in if the cmd has at least 1 argument AND it is a built in
	if (cmd->argcount > 0 && is_built_in(cmd->cmd_args[0]) == 1)
		cmd->is_built_in = true;
	else
		cmd->is_built_in = false;

	return (cmd);
}

//converts every token list into cmds, setting all info needed for execution
void	load_cmd_block(t_token **head)
{
	int	i;

	if (g_meta->state == MSTATE_NORMAL)
	{
		i = 0;
		while (head[i])
			i++;
		g_meta->cmd_block = ft_calloc(i + 1, sizeof(t_cmd *));
		g_meta->pipes = ft_calloc(i, sizeof(int *));
		g_meta->cmd_nb = i;

		i = -1;
		while (++i < g_meta->cmd_nb - 1)	//creates potentially needed pipes
		{
			g_meta->pipes[i] = ft_calloc(2, sizeof(int));
			pipe(g_meta->pipes[i]);
		}

		//actual token conversion loop
		i = -1;
		while (head[++i])
			g_meta->cmd_block[i] = tokens_to_cmd(&head[i], i);
	}
}
