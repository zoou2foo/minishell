/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/02/20 14:53:43 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if there is a token error with pipes
bool	check_pipe_error(t_token *node)
{
	g_meta->cmd_nb = 1;
	if (g_meta->state == MSTATE_NORMAL)
	{
		while (node)
		{
			if (node->type == TTYPE_PIPE)
			{
				if (!node->prev || !node->next || node->next->type == TTYPE_PIPE)
					return (true);
				g_meta->cmd_nb++; //adds 1 cmd slot for every pipe
			}
			node = node->next;
		}
	}
	return (false);
}

//create the final token array (one list per cmd)
t_token	**make_token_array(t_token *node)
{
	t_token	**token_array;
	int		i;

	token_array = ft_calloc(g_meta->cmd_nb + 1, sizeof(t_token *));
	token_array[0] = node;
	i = 0;
	while (node)
	{
		if (node->type == TTYPE_PIPE)
		{
			if (node->next)
			{
				node = node->next;
				token_array[++i] = node;
				destroy_token(node->prev);
			}
		}
		node = node->next;
	}
	return (token_array);
}

//print_token_list(head, true);			//DEBUG
//converts the given input line into a "true" finalized token list
t_token	**parse_line(char *line)
{
	t_token	*head;

	head = NULL;
	create_token_list(line, &head);
	if (g_meta->state != MSTATE_NORMAL)
	{
		free_token_list(head);
		return (NULL);
	}
	expand_token_list(head);
	head = remove_empty_list(head);
	head = merge_token_list(head);
	if (!check_pipe_error(head))
		return (make_token_array(head));

	throw_error(ERR_TOKEN);
	g_meta->state = MSTATE_O_PIPE;
	g_meta->exit_status = 2;
	free_token_list(head);
	return (NULL);
}
