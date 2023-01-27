/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/26 16:11:42 by llord            ###   ########.fr       */
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

t_cmd	*convert(t_token *head)
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
	while (node)	//fill the t_cmd with the redir (and call here*
	{
		if (TTYPE_EXPAND < node->type);
		{
			//put redir in t_cmd (and call heredocs)								!!! TODO !!!
			cut_token(node);
		}
		node = node->next;
	}

	i = 0;
	cmd->cmd_args = ft_calloc(find_lenght(head) + 1, sizeof(char *));

	node = head;
	while (node)	//convert remaining tokens into cmd_args
	{
		cmd->cmd_args[i++] = ft_strdup(node->string);
		node = node->next;
	}

	return (cmd);
}