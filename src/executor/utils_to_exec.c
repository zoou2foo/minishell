/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 11:51:36 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CHecks if the given cmd_arg is a built-in (1 = true, 0 = false)
int	is_built_in(char *cmd_arg)
{
	if ((ft_strncmp(cmd_arg, "cd", 2) == 0)
		|| (ft_strncmp(cmd_arg, "echo", 4) == 0)
		|| (ft_strncmp(cmd_arg, "env", 3) == 0)
		|| (ft_strncmp(cmd_arg, "exit", 4) == 0)
		|| (ft_strncmp(cmd_arg, "export", 6) == 0)
		|| (ft_strncmp(cmd_arg, "pwd", 3) == 0)
		|| (ft_strncmp(cmd_arg, "unset", 5) == 0))
		return (1);
	else
		return (0);
}

// Executes the built-in called via the first cmd_arg
void	execute_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0)
		change_dir(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0)
		do_echo(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "env", 3) == 0)
		get_env();
	else if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
		do_exit(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		do_export(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0)
		get_pwd();
	else if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
		do_unset(cmd);
}

// Checks if the built-in should be executed in a child process via the first cmd_arg
int	built_ins_childable(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd_args[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0)
		return (1);
	else
		return (0);
}