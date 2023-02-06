/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/03 11:41:14 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use global var. Void.
// Look for "path" in env. Split at ":". Then, join "/" aftet each section
// added metadata->path. Call a function at the end to deal with errors.
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

//in case that previous function doesn't find the variable. No need to receive
// or return anything
void	error_fill_path(void)
{
	write(2, "Environment variables not found\n", 32);
	free(metadata); // should add exit status 127
}

// Return nothing. Receive t_cmd to check if the cmd exists and the executable
// exists.
// Then, execute through execve.
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