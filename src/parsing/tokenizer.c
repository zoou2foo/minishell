/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/19 12:58:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

enum e_ttype
{
	TTYPE_ERROR		= -1,
	TTYPE_EMPTY		= 0,
	TTYPE_NORMAL	= 1,	// _	(cmds/args)
	TTYPE_S_QUOTE	= 2,	//'_'	(string without expansion)
	TTYPE_D_QUOTE	= 3,	//"_"	(string with expansion)
	TTYPE_EXPAND	= 4,	//$_	(expansion)
	TTYPE_REDIR_IN	= 5,	// <	(input path)
	TTYPE_HEREDOC	= 6,	//<<	(heredoc EOF word)
	TTYPE_S_RDR_OUT	= 7,	// >	(output path (replace))
	TTYPE_D_RDR_OUT	= 8,	//>>	(output path (append))
	TTYPE_PIPE		= 9		// |	(pipe)
};

t_token	*find_tail(t_token *head)
{
	t_token	*node;

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

//creates/extends the token list
void	add_token(t_token *token, t_token **head)
{
	t_token *node;

	if (*head)
	{
		node = find_tail(*head);
		node->next = token;
		node->next->prev = node;
	}
	else
		*head = token;
}

//creates a new token
t_token *new_token(char *str, int len, int type)
{
	t_token	*token;
	int		i;

	token = ft_calloc(1, sizeof(t_token));
	if (len)
	{
		token->string = ft_calloc(len + 2, sizeof(char));
		i = -1;
		while (++i < len + 1)
		{
			token->string[i] = str[i];
		}
		token->string[i] = '\0';
	}
	token->type = type;
	return (token);
}

bool	is_space(char c) //à mettre dans libft
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (true);
	return (false);
}

bool	is_capital(char c) //à mettre dans libft
{
	if ('A' <= c && c <= 'Z')
		return (true);
	return (false);
}

t_token	*tokenize_input(char *line)
{
	t_token	*head;
	int		len;
	int		i;

	head = NULL;
	i = -1;
	while (line[++i])		//when making functions with this, make sure they return len
	{
		len = 0;
		while (is_space(line[i]))
			++i;

		//deals with pipes
		if (line[i] == '|')
			add_token(new_token(NULL, 0, TTYPE_PIPE), &head);

		//deals with output redirection
		else if (line[i] == '>')
		{
			if (line[i + 1] != '>')
				add_token(new_token(NULL, 0, TTYPE_S_RDR_OUT), &head);
			else
			{
				len++;
				add_token(new_token(NULL, 0, TTYPE_D_RDR_OUT), &head);
			}
		}

		//deals with input redirection
		else if (line[i] == '<')
		{
			if (line[i + 1] != '<')
				add_token(new_token(NULL, 0, TTYPE_REDIR_IN), &head);
			else
			{
				len++;
				add_token(new_token(NULL, 0, TTYPE_HEREDOC), &head);	//================( HERE IS HEREDOC )================
			}
		}

		//deals with single quotes
		else if (line[i] == '\'')
		{
			len++;
			while (line[i + len] && line[i + len] != '\'')
				len++;
			if (!line[i + len])		//"exits" when unterminated quotes
				return (NULL);
			add_token(new_token(&line[i + 1], len - 2, TTYPE_S_QUOTE), &head);
		}

		//deals with double quotes
		else if (line[i] == '\"')
		{
			len++;
			while (line[i + len] && line[i + len] != '\"')
				len++;
			if (!line[i + len])		//"exits" when unterminated quotes
				return (NULL);
			add_token(new_token(&line[i + 1], len - 2, TTYPE_D_QUOTE), &head);
		}

		//deals with expansions outside of ""
		else if (line[i] == '$')
		{
			len++;
			while (line[i + len] && is_capital(line[i + len]))
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
