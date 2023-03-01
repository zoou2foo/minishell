/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/03/01 09:20:59 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a new token
t_token	*new_token(char *str, int len, int type)
{
	t_token	*node;
	int		i;

	len++;
	node = ft_calloc(1, sizeof(t_token));
	node->string = ft_calloc(len + 1, sizeof(char));
	if (0 < len)
	{
		i = -1;
		while (++i < len)
		{
			node->string[i] = str[i];
		}
		node->string[i] = '\0';
	}
	if (len <= 0 && type < TTYPE_EXPAND)
		node->type = TTYPE_EMPTY;
	else
		node->type = type;
	return (node);
}

//creates/extends the token list
void	add_token(t_token *node, t_token **head)
{
	t_token	*tail;

	if (*head)
	{
		tail = find_tail(*head);
		tail->next = node;
		tail->next->prev = tail;
	}
	else
		*head = node;
}

//merges two token's strings into one (reusing the first node)
t_token	*merge_tokens(t_token *node, t_token *next)
{
	char	*str;

	if (node->string && next->string)
		str = ft_strjoin(node->string, next->string);
	else if (node->string)
		str = ft_strdup(node->string);
	else if (next->string)
		str = ft_strdup(next->string);
	else
		str = ft_calloc(1, sizeof(char));

	ft_free_null(node->string);
	node->string = str;

	node->next = next->next;
	if (node->next)
		node->next->prev = node;

	free_token(next);
	return (node);
}

//inserts a token between two others
t_token	*insert_token(t_token *node, t_token *prev, t_token *next)
{
	if (node)
	{
		if (prev)
		{
			node->prev = prev;
			prev->next = node;
		}
		if (next)
		{
			node->next = next;
			next->prev = node;
		}
	}
	return (node);
}

//replaces a token with another
t_token	*replace_token(t_token *new, t_token *old)
{
	if (new && old)
	{
		new->next = old->next;
		new->prev = old->prev;
		free_token(old);
	}
	return (new);
}
