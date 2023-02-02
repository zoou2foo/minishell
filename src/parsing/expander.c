/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/02 14:41:56 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str1)
{
	char	*str2;
	int		i;
	int		j;
	int		k;

	i = -1;
	str2 = NULL;
	/*
	if (str1[0] == '?' && str1[1] == '\0')		//doesn't work
	{
		ft_free_null(str1);
		printf("lol\n");
		return (ft_itoa(metadata->exit_status));
	}
	*/
	while (environ[++i])
	{
		j = 0;
		if (ft_strncmp(str1, environ[i], ft_strlen(str1)) == 0)
		{
			j += ft_strlen(str1);
			if (environ[i][j] != '=')
				continue;
			j++;
			str2 = ft_calloc(sizeof(char), ft_strlen(environ[i]));
			k = 0;
			while (environ[i][j])
			{
				str2[k] = environ[i][j];
				j++;
				k++;
			}
			break ;
		}
	}
	/*
	if (!str2)				//must stop process somehow?
		return (str1);
	*/
	ft_free_null(str1);
	return (str2);
}

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

char	*expand_quote(char *str1)
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
			while (str1[i + len] && is_capital(str1[i + len]))		//USE ANOTHER FUNCTION
				len += 1;
			tmp = expand(trimstr(&str1[i], len));
			i += len - 1;
		}
		else
		{
			tmp = ft_calloc(2, sizeof(char));
			tmp[0] = str1[i];
		}
		if (tmp)											//prevent returning null strings
			str2 = ft_strjoin_free(str2, tmp);
		i++;
	}
	ft_free_null(str1);										//frees old string
	return (str2);
}