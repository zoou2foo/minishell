/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 09:51:28 by llord            ###   ########.fr       */
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
	while (metadata->env[i])
	{
		if (ft_strncmp(metadata->env[i], "PATH=", 5) == 0)
		{
			metadata->paths = ft_split(&metadata->env[i][5], ':');
			i = 0;

			while (metadata->paths[i])
			{
				tmp = ft_strjoin(metadata->paths[i], "/");		//adds final / so we don't have to during excecution
				ft_free_null(metadata->paths[i]);
				metadata->paths[i] = tmp;
				i++;
			}
			return ;
		}
		i++;
	}
	throw_error(ERR_ENV);
	ft_free_null(metadata); // should add exit status 127
}

//throws out a specified error message
void	throw_error(char *str)
{
	write(2, str, ft_strlen(str));
}

// Checks if a given cmd exists and is executable, then execute it
// Execve automatically exit() when used
void	exec_with_paths(t_cmd *cmd)
{
	char	*cmd_path;
	int		i;

	i = -1;

	if (access(cmd->cmd_args[0], F_OK | X_OK) == 0)
		execve(cmd->cmd_args[0], cmd->cmd_args, metadata->env);
	while (metadata->paths[++i])
	{
		cmd_path = ft_strjoin(metadata->paths[i], cmd->cmd_args[0]);
		if (!access(cmd_path, F_OK | X_OK))
			execve(cmd_path, cmd->cmd_args, metadata->env);
		ft_free_null(cmd_path);
	}
}