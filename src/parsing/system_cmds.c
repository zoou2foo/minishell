/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/01/23 14:58:12 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_path_tab(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (metadata->env[i])
	{
		if (ft_strncmp(metadata->env[i], "PATH=", 5) == 0)
		{
			metadata->path = ft_split(metadata->env[i], ':');
			i = 0;
			while (metadata->path[i])
			{
				tmp = ft_strjoin(metadata->path[i], "/");
				ft_free_null(metadata->path[i]);
				metadata->path[i] = tmp;
				i++;
			}
			metadata->path[0] = ft_strtrim(metadata->path[0], "PATH=");
			//*metadata->path[0] += 5;
			return ;
		}
		i++;
	}
	error_fill_path();
}

void	error_fill_path(void)
{
	write(2, "Environment variables not found\n", 32);
	free(metadata);
}

/*
char	*find_cmd(t_token **token_array)
{
	int		i;
	char	*cmds;

	i = 0;
	if (ft_strncmp(token_array[0], "/", 1) == 0)
	{
		if (access(token_array, X_OK) == 0)
			return (token_array);
	}
	while (metadata->path[i])
	{
		cmds = ft_strjoin(metadata->path[i], *token_array);
		if (access(cmds, F_OK | X_OK) == 0)
			return (cmds);
		free(cmds);
		i++;
	}
	return (NULL);
} */