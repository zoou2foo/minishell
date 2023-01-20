/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/20 11:09:35 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_expansion(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = NULL;
	while (environ[i])
	{
		if (ft_strncmp(str, environ[i], ft_strlen(str)) == 0)
		{
			tmp = ft_calloc(sizeof(char), ft_strlen(environ[i]));
			while (environ[i][j] != '=')
				j++;
			j += 1;
			while (environ[i][j])
			{
				tmp[k] = environ[i][j];
				j++;
				k++;
			}
			break ;
		}
		i++;
	}
	//we need to free the old string from node
	return (tmp);
}

char	*do_expand_in_dbl_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i += 1;
			do_expansion(str + i);
			return (str);
		}
		i++;
	}
	return (str);
}