/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/02/23 14:31:42 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if the given char is still inside an expansion
bool	is_in_expansion(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?' || c == '!')
		return (true);
	return (false);
}

//deals with output redirection
int	find_redir_out(char *line, int i, t_token **head)
{
	int	len;

	len = 0;
	if (line[i + 1] != '>')
		add_token(new_token(NULL, -1, TTYPE_S_RDR_OUT), head);
	else
	{
		len++;
		add_token(new_token(NULL, -1, TTYPE_D_RDR_OUT), head);
	}
	return (len);
}

//deals with input redirection
int	find_redir_in(char *line, int i, t_token **head)
{
	int	len;

	len = 0;
	if (line[i + 1] != '<')
		add_token(new_token(NULL, -1, TTYPE_REDIR_IN), head);
	else
	{
		len++;
		add_token(new_token(NULL, -1, TTYPE_HEREDOC), head);
	}
	return (len);
}

//deals with quotes
int	find_quote(char *line, int i, t_token **head, char c)
{
	int	len;

	len = 1;
	while (line[i + len] && line[i + len] != c)
		len++;
	if (!line[i + len]) //makes us ignore the cmd line when unterminated quotes
	{
		throw_error(ERR_QUOTE);
		g_meta->state = MSTATE_O_BRACK;
		g_meta->exit_status = 2;
		return (0);
	}
	if (c == '\"')
		add_token(new_token(&line[i + 1], len - 2, TTYPE_D_QUOTE), head);
	else
		add_token(new_token(&line[i + 1], len - 2, TTYPE_S_QUOTE), head);
	return (len);
}

//deals with expansions and normal inputs
int	find_leftover(char *line, int i, t_token **head)
{
	int	len;

	len = 0;
	if (line[i] == '$') //deals with expansions outside of ""
	{
		len++;
		while (is_in_expansion(line[i + len]))
			len++;
		len--;
		add_token(new_token(&line[i + 1], len - 1, TTYPE_EXPAND), head);
	}
	else //deals with normal cmds/args input
	{
		while (line[i + len] && !ft_isspace(line[i + len]) && !ft_strchr("|><\'\"$", line[i + len]))
			len++;
		len--;
		add_token(new_token(&line[i], len, TTYPE_NORMAL), head);
	}
	return (len);
}
