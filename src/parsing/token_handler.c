/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/27 15:24:04 by llord            ###   ########.fr       */
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

//creates a new token
t_token *new_token(char *str, int len, int type)
{
	t_token	*node;
	int		i;

	len++;
	node = ft_calloc(1, sizeof(t_token));
	if (0 < len)
	{
		node->string = ft_calloc(len + 1, sizeof(char));
		i = -1;
		while (++i < len)
		{
			node->string[i] = str[i];
		}
		node->string[i] = '\0';
	}
	node->type = type;
	return (node);
}

//creates/extends the token list
void	add_token(t_token *node, t_token **head)
{
	t_token *tail;

	if (*head)
	{
		tail = find_tail(*head);
		tail->next = node;
		tail->next->prev = tail;
	}
	else
		*head = node;
}

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

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

//finds the head end of a token list (may loop if list is circular)
t_token	*find_head(t_token *tail)
{
	t_token	*node;

	node = tail;
	while (node->prev)
		node = node->prev;
	return (node);
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

//deletes a token and links its next and prev together
//tries to return the next, then the prev, then NULL
t_token	*cut_token(t_token *node)
{
	t_token	*ret;

	ret = node;
	if (node)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
		{
			node->next->prev = node->prev;
			ret = node->next;
		}
		else if (node->prev)
			ret = node->prev;
		free_token(node);
	}
	return (ret);
}

//deletes a token without relinking
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
