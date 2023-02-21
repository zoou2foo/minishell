/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 12:59:36 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//throws out a specified error message
void	throw_error(char *str)
{
	write(2, str, ft_strlen(str));
}

// Looks for "path" in env. Splits at ":". Then, join "/" after each section;
//no need to add it during execution
void	fill_path_tab(void)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_meta->env[++i])
	{
		if (is_same(g_meta->env[i], "PATH="))
		{
			g_meta->paths = ft_split(&g_meta->env[i][5], ':');
			i = -1;
			while (g_meta->paths[++i])
			{
				tmp = ft_strjoin(g_meta->paths[i], "/");
				ft_free_null(g_meta->paths[i]);
				g_meta->paths[i] = tmp;
			}
			return ;
		}
	}
	throw_error(ERR_PATH);
	g_meta->exit_status = EXIT_FAILURE;
}

void	free_path_tab(void)
{
	int		i;

	i = -1;
	while (g_meta->paths[++i])
		ft_free_null(g_meta->paths[i]);
	ft_free_null(g_meta->paths);
}

void	check_cmd_path(int i, t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(g_meta->paths[i], cmd->cmd_args[0]);
	if (!access(cmd_path, F_OK | X_OK))
		g_meta->exit_status = execve(cmd_path, cmd->cmd_args, g_meta->env);
	ft_free_null(cmd_path);
}

// Checks if a given cmd exists and is executable, then execute it
// Execve automatically exit() when used
// call one time fill_path_tab here, instead of everywhere
// after execve(); need to free g_meta->paths right away, not at the very end
void	exec_with_paths(t_cmd *cmd)
{
	int		i;

	if (g_meta->env)
	{
		if (access(cmd->cmd_args[0], F_OK | X_OK) == 0)
		{
			if (cmd->fdin > 0) //need to do a check on fd
				close(cmd->fdin);
			if (cmd->fdout > 0)
				close(cmd->fdout);
			execve(cmd->cmd_args[0], cmd->cmd_args, g_meta->env);
		}
		fill_path_tab();
		if (g_meta->paths[0])
		{
			i = -1;
			while (g_meta->paths[++i])
				check_cmd_path(i, cmd);
			throw_error(ERR_CMD);
			g_meta->exit_status = 127;
			free_path_tab();
		}
		return ;
	}
	throw_error(ERR_ENV);
	g_meta->exit_status = 127;
	//close_fds(cmd);
}
