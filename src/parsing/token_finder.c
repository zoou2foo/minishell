/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:33:52 by llord             #+#    #+#             */
/*   Updated: 2023/02/24 11:02:11 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//finds lenght of a token list (may loop if list is circular)
int	find_length(t_token *head)
{
	t_token	*node;
	int		i;

	node = head;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

//finds the tail end of a token list (may loop if list is circular)
t_token	*find_tail(t_token *head)
{
	t_token	*node;

	if (!head)
		node = new_token("", 0, TTYPE_ERROR);
	else
	{
		node = head;
		while (node->next)
			node = node->next;
	}
	return (node);
}

//finds the head end of a token list (may loop if list is circular)
t_token	*find_head(t_token *tail)
{
	t_token	*node;

	if (!tail)
		node = new_token("", 0, TTYPE_ERROR);
	else
	{
		node = tail;
		while (node->prev)
			node = node->prev;
	}
	return (node);
}
