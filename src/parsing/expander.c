/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/24 11:09:09 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expands an expansion string ($_)
char	*expand(char *str1)
{
	char	*str2;
	int		i;
	int		j;
	int		k;

	str2 = ft_calloc(2, sizeof(char));
	i = -1;
	if (str1[0])
	{
		if (str1[0] == '?' && str1[1] == '\0')
		{
			ft_free_null(str1);
			return (ft_itoa(g_meta->exit_status));
		}
		while (g_meta->env[++i])
		{
			j = 0;
			if (is_same(g_meta->env[i], str1))
			{
				j += ft_strlen(str1);
				if (g_meta->env[i][j] != '=')
					continue ;
				j++;
				ft_free_null(str2);
				str2 = ft_calloc(ft_strlen(g_meta->env[i]), sizeof(char));
				k = 0;
				while (g_meta->env[i][j])
				{
					str2[k] = g_meta->env[i][j];
					j++;
					k++;
				}
				break ;
			}
		}
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

//expands inside a quote string ("$_") if needed
char	*expand_quote(char *str1)
{
	char	*str2;
	char	*tmp;
	int		i;
	int		len;

	str2 = ft_calloc(1, sizeof(char));
	i = 0;
	while (str1[i])
	{
		len = 0;
		if (str1[i] == '$')
		{
			i += 1;
			while (is_in_expansion(str1[i + len]))
				len++;
			tmp = expand(trimstr(&str1[i], len));
			i += len - 1;
		}
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
