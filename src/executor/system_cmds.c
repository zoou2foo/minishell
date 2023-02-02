/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/02 14:43:46 by vjean            ###   ########.fr       */
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
				tmp = ft_strjoin(metadata->path[i], "/");		//adds final / so we don't have to during excecution
				ft_free_null(metadata->path[i]);
				metadata->path[i] = tmp;
				i++;
			}
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

void	exec_with_paths(t_cmd *cmd)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (metadata->path[++i])
	{
		cmd_path = ft_strjoin(metadata->path[i], cmd->cmd_args[0]);
		if (!access(cmd_path, F_OK | X_OK))
			execve(cmd_path, cmd->cmd_args, metadata->env);
		ft_free_null(cmd_path);
	}
}