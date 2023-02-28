/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 11:29:28 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//finds the PATH variable from g_meta->env and splits it into usable paths
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

//tries to execute a cmd using g_meta->paths[i]
void	try_cmd_path(int i, t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(g_meta->paths[i], cmd->cmd_args[0]);
	if (!access(cmd_path, F_OK | X_OK))
		g_meta->exit_status = execve(cmd_path, cmd->cmd_args, g_meta->env);
	ft_free_null(cmd_path);
}

//tries to execute a given cmd using g_meta->paths
void	exec_with_paths(t_cmd *cmd)
{
	int		i;

	if (g_meta->env)
	{
		if (access(cmd->cmd_args[0], F_OK | X_OK) == 0)
			execve(cmd->cmd_args[0], cmd->cmd_args, g_meta->env);
		fill_path_tab();
		if (g_meta->paths[0])
		{
			i = -1;
			while (g_meta->paths[++i])
				try_cmd_path(i, cmd);
			throw_error(ERR_CMD);
			g_meta->exit_status = 127;
			ft_free_tab((void **)g_meta->paths);
		}
		return ;
	}
	throw_error(ERR_ENV);
	g_meta->exit_status = 127;
}
