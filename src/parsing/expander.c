/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/20 12:48:42 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_expansion(char *str1)
{
	char	*str2;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str2 = NULL;
	while (environ[i])
	{
		if (ft_strncmp(str1, environ[i], ft_strlen(str1)) == 0)
		{
			str2 = ft_calloc(sizeof(char), ft_strlen(environ[i]));
			while (environ[i][j] != '=')
				j++;
			j += 1;
			while (environ[i][j])
			{
				str2[k] = environ[i][j];
				j++;
				k++;
			}
			break ;
		}
		i++;
	}
	//we need to free the old string from node
	return (str2);
}

char	*trimstr(char *str1, int len)
{
	char	*str2;
	int		i;

	str2 = ft_calloc(len, sizeof(char));
	i = 0;
	while (i < len)
	{
		str2[i] = str1[i];
		i++;
	}
	return (str2);
}

char	*do_expand_in_dbl_quotes(char *str1)
{
	char	*str2;
	char	*tmp;
	int		i;
	int		len;

	str2 = ft_calloc(1, sizeof(char));
	i = 0;
	len = 0;
	while (str1[i])
	{
		if (str1[i] == '$')
		{
			i += 1;
			while (str1[i + len] && str1[i + len] != ' ')		//is_capital?
				len += 1;
			len -= 1;
			tmp = do_expansion(trimstr(&str1[i], len));
			printf("%s\n", tmp);
			i += len;
		}
		else
		{
			tmp = ft_calloc(2, sizeof(char));
			tmp[0] = str1[i];
		}
		str2 = ft_strjoin_free(str2, tmp);
		//printf("%s\n", str2);
		i++;
	}
	return (str2);
}n