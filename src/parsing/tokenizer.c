/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/20 13:04:28 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
				add_token(new_token(NULL, -1, TTYPE_HEREDOC), &head);	//================( HERE IS HEREDOC )================
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

t_token	*expand_tokens(t_token *head)
{
	t_token	*node;

	node = head;
	while (node->next)
		node = node->next;
	return (node);
}
