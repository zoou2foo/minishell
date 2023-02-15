/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 14:22:11 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Looks for "path" in env. Splits at ":". Then, join "/" after each section;
//no need to add it during execution
void	fill_path_tab(void)
{
	int		i;
	char	*tmp;

	i = 0;

	while (g_meta->env[i])
	{
		if (is_same(g_meta->env[i], "PATH="))
		{
			g_meta->paths = ft_split(&g_meta->env[i][5], ':');
			i = 0;

			while (g_meta->paths[i])
			{
				tmp = ft_strjoin(g_meta->paths[i], "/");
				ft_free_null(g_meta->paths[i]);
				g_meta->paths[i] = tmp;
				i++;
			}
			return ;
		}
		i++;
	}
	throw_error(ERR_PATH);
	g_meta->exit_status = EXIT_FAILURE;
}

//throws out a specified error message
void	throw_error(char *str)
{
	write(2, str, ft_strlen(str));
}

// Checks if a given cmd exists and is executable, then execute it
// Execve automatically exit() when used
// call one time fill_path_tab here, instead of everywhere
// after execve(); need to free g_meta->paths right away, not at the very end
void	exec_with_paths(t_cmd *cmd)
{
	char	*cmd_path;
	int		i;

	if (access(cmd->cmd_args[0], F_OK | X_OK) == 0)
		execve(cmd->cmd_args[0], cmd->cmd_args, g_meta->env);

	if (g_meta->env)
		fill_path_tab();

	i = -1;
	while (g_meta->paths[++i])
	{
		cmd_path = ft_strjoin(g_meta->paths[i], cmd->cmd_args[0]);
		if (!access(cmd_path, F_OK | X_OK))
			g_meta->exit_status = execve(cmd_path, cmd->cmd_args, g_meta->env);
		ft_free_null(cmd_path);
	}
	throw_error(ERR_CMD);
	g_meta->exit_status = 127;
}
