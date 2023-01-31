/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/01/31 14:36:38 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_path_tab(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			metadata->path = ft_split(&environ[i][5], ':');
			i = 0;
			while (metadata->path[i])
			{
				tmp = ft_strjoin(metadata->path[i], "/");
				ft_free_null(metadata->path[i]);
				metadata->path[i] = tmp;
				i++;
			}
			//metadata->path[0] = ft_strtrim(metadata->path[0], "PATH=");
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
	free(metadata); // should add exit status 127
}

char	*find_cmd(t_cmd *cmd)
{
	int		i;
	char	*cmd_found;

	i = 0;
	if (ft_strncmp(cmd->cmd_args[0], "/", 1) == 0)
	{
		if (access(*cmd->cmd_args, X_OK) == 0)
			return (*cmd->cmd_args);
	}
	while (metadata->path[i])
	{
		cmd_found = ft_strjoin(metadata->path[i], *cmd->cmd_args);
		if (access(cmd_found, F_OK | X_OK) == 0)
		{
			printf("found\n"); // juste pour voir si ça fonctionne
			return (cmd_found);
		}
		free(cmd_found);
		i++;
	}
	return (NULL); // should add exit 127 as cmd not found
}