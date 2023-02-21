/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 08:54:08 by vjean             #+#    #+#             */
/*   Updated: 2023/02/20 08:54:39 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to check if var exist already
//if not found, return -1
int	find_var(char *str)
{
	int	len;
	int	i;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	i = 0;
	while (g_meta->env[i])
	{
		if (ft_strncmp(g_meta->env[i], str, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	is_valid_name(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i > 0 && str[i] == '=')
		return (TRUE);
	return (FALSE);
}
