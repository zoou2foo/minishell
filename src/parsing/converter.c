/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/27 12:27:47 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	from token array

	create one t_cmd per line

	loop on all lines multiple times:
		- once to merge tokens (ex > type + string = string w/ type >)
		- once to fill the t_cmd with the redir (and call here*
		10
		doc funct)
		- once to convert remaining tokens into cmd_args

	free all tokens

	//AFTER WE SHOULD TEST/INTEGRATE THE BUILT-INS

*/

t_cmd	*tokens_to_cmd(t_token *head)			//TODO : set the "has_pipes"
{
	t_cmd	*cmd;
	t_token	*node;
	int		i;


	node = head;
	while (node)	//merge tokens (ex > type + string = string w/ type >)
	{
		if (node->next && node->next->type <= TTYPE_EXPAND && TTYPE_EXPAND < node->type)
			node = merge_tokens(node, node->next);
		node = node->next;
	}

	cmd = ft_calloc(1, sizeof(t_cmd));

	node = head;
	while (node)	//fill the t_cmd with the redir (and call heredocs)
	{
		if (TTYPE_EXPAND < node->type)
		{

			if (node->type == TTYPE_S_RDR_OUT)
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = false;
				cmd->has_output = true;
			}
			else if (node->type == TTYPE_D_RDR_OUT)
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = true;					//did I swap them??
				cmd->has_output = true;
			}
			else if (node->type == TTYPE_REDIR_IN)
			{
				ft_free_null(cmd->input);
				cmd->input = ft_strdup(node->string);
				cmd->has_input = true;
			}
			else if (node->type == TTYPE_HEREDOC)
			{
				ft_free_null(cmd->input);
				//heredoc function
				cmd->has_input = true;
			}
			cut_token(node);
		}
		node = node->next;
	}

	i = 0;
	cmd->argcount = find_lenght(head);
	cmd->cmd_args = ft_calloc(cmd->argcount + 1, sizeof(char *));

	node = head;
	while (node)	//convert remaining tokens into cmd_args
	{
		cmd->cmd_args[i++] = ft_strdup(node->string);
		node = node->next;
	}

	return (cmd);
}