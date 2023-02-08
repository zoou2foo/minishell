/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/02/08 14:12:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//converts the given input line into a "true" finalized token list
t_token	**parse_line(char *line)
{
	t_token	**token_array;
	t_token	*head;
	t_token	*node;
	int		i;


	head = create_token_list(line);
	//print_token_list(head, true);			//DEBUG

	expand_token_list(head);
	//print_token_list(head, false);		//DEBUG

	head = merge_token_list(head);
	//print_token_list(head, false);		//DEBUG

	head = remove_empty_list(head);
	//print_token_list(head, false);		//DEBUG

	i = 1;		//at least 1 cmd to execute
	node = head;
	while (node)
	{
		if (node->type == TTYPE_PIPE)
			i++;
		node = node->next;
	}
	token_array = ft_calloc(i + 1, sizeof(t_token *));
	node = head;
	token_array[0] = head;
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
