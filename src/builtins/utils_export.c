/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 08:54:08 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:09:44 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if a given var is already present in g_meta->env
int	find_var(char *var)
{
	int	len;
	int	i;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	i = 0;
	while (g_meta->env[i])
	{
		if (ft_strncmp(g_meta->env[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//checks if a given str could be a valid ENV variable name
bool	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (FALSE);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i > 0 && str[i] == '=')
		return (TRUE);
	return (FALSE);
}
