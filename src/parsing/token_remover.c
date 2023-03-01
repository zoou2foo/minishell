/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:35:25 by llord             #+#    #+#             */
/*   Updated: 2023/03/01 09:21:04 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//frees a token entirely
void	free_token(t_token *node)
{
	if (node)
	{
		if (node->string)
			ft_free_null(node->string);
		ft_free_null(node);
	}
}

//frees a token list entirely
void	free_token_list(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		free_token(head);
		head = next;
	}
}

//deletes a token without relinking its prev and next
void	destroy_token(t_token *node)
{
	if (node)
	{
		if (node->prev)
			node->prev->next = NULL;
		if (node->next)
			node->next->prev = NULL;
		free_token(node);
	}
}

//deletes a token and links its next and prev together
//tries to return the prev, then the next
//if the token has no prev or next, empties and returns it instead
t_token	*cut_token(t_token *node)
{
	t_token	*ret;

	ret = NULL;
	if (node)
	{
		if (node->next)
		{
			node->next->prev = node->prev;
			ret = node->next;
		}
		if (node->prev)
		{
			node->prev->next = node->next;
			ret = node->prev;
		}
		if (!node->prev && !node->next)
		{
			return (empty_token(node));
		}
		free_token(node);
	}
	return (ret);
}

//deletes the info inside a token
t_token	*empty_token(t_token *node)
{
	if (node)
	{
		node->prev = NULL;
		node->next = NULL;
		if (node->string)
			ft_free_null(node->string);
		node->string = ft_calloc(1, sizeof(char *));
		node->type = TTYPE_EMPTY;
	}
	return (node);
}
