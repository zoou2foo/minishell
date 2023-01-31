/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/31 12:25:50 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//splits the cmd line along pipes and
t_token	**parse_line(char *line)				//check validity of token list beforehand
{
	t_token	**token_array;
	t_token	*head;
	t_token	*node;
	int		i;

	head = create_token_list(line);
//	print_token_list(head);				//DEBUG
	expand_token_list(head);
//	print_token_list(head);				//DEBUG
	head = merge_token_list(head);
//	print_token_list(head);				//DEBUG

	i = 1;		//1 because at least one cmd to execute
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
