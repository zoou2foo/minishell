/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:10:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 13:31:30 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Looks for "path" in env. Splits at ":". Then, join s"/" after each section
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
	throw_error(ERR_PATH);
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

	if (access(cmd->cmd_args[0], F_OK | X_OK) == 0)
		execve(cmd->cmd_args[0], cmd->cmd_args, metadata->env);

	fill_path_tab();	//call une seule fois fill_path_tab ici au lieu de le mettre partout

	i = -1;
	while (metadata->paths[++i])
	{
		cmd_path = ft_strjoin(metadata->paths[i], cmd->cmd_args[0]);
		if (!access(cmd_path, F_OK | X_OK))
			execve(cmd_path, cmd->cmd_args, metadata->env);
		ft_free_null(cmd_path); //free metadata->paths
	}
	throw_error(ERR_CMD);
	//ft_free_array(metadata->paths)							//IMPLEMENT ME (add fct to libft)
}