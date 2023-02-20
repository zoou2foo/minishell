/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/02/20 13:27:57 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if a given token type is mergable
bool	is_mergeable(int type)
{
	if (TTYPE_NORMAL <= type && type <= TTYPE_EXPAND)
		return (true);
	return (false);
}

//converts the given input line in a raw token list
void	create_token_list(char *line, t_token **head)
{
	int		len;
	int		i;

	i = -1;
	while (line[++i])
	{
		len = 0;
		while (ft_isspace(line[i]))
			++i;
		if (line[i] == '|') //deals with pipes
			add_token(new_token(NULL, -1, TTYPE_PIPE), head);
		else if (line[i] == '>')
			len += find_redir_out(line, i, head);
		else if (line[i] == '<')
			len += find_redir_in(line, i, head);
		else if (line[i] == '\'')
			len += find_quote(line, i, head, '\'');
		else if (line[i] == '\"')
			len += find_quote(line, i, head, '\"');
		else
			len += find_leftover(line, i, head);
		if (*head && i > 0 && !ft_isspace(line[i - 1])) //notes if the current and previous tokens are joined
			find_tail(*head)->is_joined = true;
		i += len;
	}
}

//expands the expandable tokens in a given token list
void	expand_token_list(t_token *head)
{
	t_token	*node;

	node = head;
	while (node)
	{
		//handles standalone expansions
		if (node->type == TTYPE_EXPAND)
		{
			//printf(" - $%s", node->string);				//DEBUG
			node->string = expand(node->string);
			//printf(" > %s\n", node->string);				//DEBUG
			if (!node->string[0])
				node->type = TTYPE_EMPTY;
		}
		//handles expansions inside double quotes
		else if (node->type == TTYPE_D_QUOTE)
		{
			//printf(" - \"%s\"", node->string);			//DEBUG
			node->string = expand_quote(node->string);
			//printf(" > \"%s\"\n", node->string);			//DEBUG
		}
		node = node->next;
	}
}

//removes the empty tokens from a given token list
t_token	*remove_empty_list(t_token *head)
{
	t_token	*node;

	node = head;
	while (node)
	{
		if (node->type == TTYPE_EMPTY)
		{
			if (node->next)
				if (!node->is_joined || !node->next->is_joined) //prevent false joins
					node->next->is_joined = false;
			node = cut_token(node);
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}
	head = find_head(node);

	return (head);
}

//merges the mergeable tokens in a given token list
t_token	*merge_token_list(t_token *head)
{
	t_token	*node;

	node = head;
	while (node->next)
	{
		if (node->next && node->next->is_joined)
		{
			if (is_mergeable(node->type) && is_mergeable(node->next->type))
			{
				//printf(" - %s + %s\n", node->string, node->next->string); 	//DEBUG
				node = merge_tokens(node, node->next);
				continue ;
			}
		}
		node = node->next;
	}
	return (find_head(node));
}
