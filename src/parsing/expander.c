/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 13:11:39 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the value of a given ENV var string
char	*get_var(char *str1, char *str2)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (g_meta->env[++i])
	{
		if (is_same(g_meta->env[i], str1, false))
		{
			j = ft_strlen(str1);
			if (g_meta->env[i][j++] != '=')
				continue ;
			ft_free_null(str2);
			str2 = ft_calloc(ft_strlen(g_meta->env[i]), sizeof(char));
			k = 0;
			while (g_meta->env[i][j])
				str2[k++] = g_meta->env[i][j++];
			break ;
		}
	}
	return (str2);
}

//expands an expansion string ($_)
char	*expand(char *str1)
{
	char	*str2;

	str2 = ft_calloc(2, sizeof(char));
	if (str1[0])
	{
		if (str1[0] == '?' && str1[1] == '\0')
		{
			ft_free_null(str1);
			return (ft_itoa(g_meta->exit_status));
		}
		str2 = get_var(str1, str2);
	}
	else
		str2[0] = '$';
	ft_free_null(str1);
	return (str2);
}

//duplicates only the first len chars of a given string
char	*trimstr(char *str1, int len)
{
	char	*str2;
	int		i;

	str2 = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		str2[i] = str1[i];
		i++;
	}
	return (str2);
}

//checks prepares the vars needed to call expand()
char	*get_expansion(char *str1, int *i)
{
	char	*tmp;
	int		len;

	*i += 1;
	len = 0;
	while (is_in_expansion(str1[(*i) + len]))
		len++;
	tmp = expand(trimstr(&str1[*i], len));
	*i += len - 1;
	return (tmp);
}

//expands inside a quote string ("$_") if needed
char	*expand_quote(char *str1)
{
	char	*str2;
	char	*tmp;
	int		i;

	str2 = ft_calloc(1, sizeof(char));
	i = 0;
	while (str1[i])
	{
		if (str1[i] == '$')
			tmp = get_expansion(str1, &i);
		else
		{
			tmp = ft_calloc(2, sizeof(char));
			tmp[0] = str1[i];
		}
		if (tmp)
			str2 = ft_strjoin_free(str2, tmp);
		i++;
	}
	ft_free_null(str1);
	return (str2);
}
