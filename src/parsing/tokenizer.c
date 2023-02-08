/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/02/08 09:58:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	is_capital(char c)		//OBSOLETE
{
	if ('A' <= c && c <= 'Z')
		return (true);
	return (false);
}

bool	is_mergeable(int type)
{
	if (TTYPE_NORMAL <= type && type <= TTYPE_EXPAND)
		return (true);
	return (false);
}

t_token	*create_token_list(char *line)
{
	t_token	*head;
	int		len;
	int		i;

	head = NULL;
	i = -1;
	while (line[++i])				//when making functions with these, make sure they return len
	{
		len = 0;
		while (is_space(line[i]))
			++i;

		//deals with pipes
		if (line[i] == '|')
			add_token(new_token(NULL, -1, TTYPE_PIPE), &head);

		//deals with output redirection
		else if (line[i] == '>')
		{
			if (line[i + 1] != '>')
				add_token(new_token(NULL, -1, TTYPE_S_RDR_OUT), &head);
			else
			{
				len++;
				add_token(new_token(NULL, -1, TTYPE_D_RDR_OUT), &head);
			}
		}

		//deals with input redirection
		else if (line[i] == '<')
		{
			if (line[i + 1] != '<')
				add_token(new_token(NULL, -1, TTYPE_REDIR_IN), &head);
			else
			{
				len++;
				add_token(new_token(NULL, -1, TTYPE_HEREDOC), &head);
			}
		}

		//deals with single quotes
		else if (line[i] == '\'')
		{
			len++;
			while (line[i + len] && line[i + len] != '\'')
				len++;
			if (!line[i + len])					//makes us ignore the cmd line when unterminated quotes
			{
				throw_error(ERR_QUOTE);
				metadata->state = MSTATE_O_BRACK;
			}
			add_token(new_token(&line[i + 1], len - 2, TTYPE_S_QUOTE), &head);
		}

		//deals with double quotes
		else if (line[i] == '\"')
		{
			len++;
			while (line[i + len] && line[i + len] != '\"')
				len++;
			if (!line[i + len])					//makes us ignore the cmd line when unterminated quotes
			{
				throw_error(ERR_QUOTE);
				metadata->state = MSTATE_O_BRACK;
			}
			add_token(new_token(&line[i + 1], len - 2, TTYPE_D_QUOTE), &head);
		}

		//deals with expansions outside of ""
		else if (line[i] == '$')
		{
			len++;
			while (line[i + len] && !is_space(line[i + len]) && line[i + len] != '$')
				len++;
			len--;
			add_token(new_token(&line[i + 1], len - 1, TTYPE_EXPAND), &head);
		}

		//deals with normal cmds/args input
		else
		{
			//while (line[i + len] && !is_space(line[i + len]) && !is_special(line[i + len]))
			while (line[i + len] && !is_space(line[i + len]) && !ft_strchr("|><\'\"$", line[i + len]))
				len++;
			len -= 1;
			add_token(new_token(&line[i], len, TTYPE_NORMAL), &head);
		}

		//notes down if the token is potentially "tied" to the previous
		if (head && (i == 0 || is_space(line[i - 1])))
			find_tail(head)->is_joined = false;
		else
			find_tail(head)->is_joined = true;

		i += len;
	}
	return (head);
}

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
				//printf(" - %s + %s\n", node->string, node->next->string);				//DEBUG
				node = merge_tokens(node, node->next);
				continue ;
			}
		}
		node = node->next;
	}
	return (find_head(node));
}

t_token	*remove_empty_list(t_token *head)			//to remove empty tokens
{
	t_token	*node;

	node = head;
	while (node)
	{
		if (node->type == TTYPE_EMPTY)
			node = cut_token(node);
		if (node->next)
			node = node->next;
		else
			break ;
	}
	head = find_head(node);

	return (head);
}
