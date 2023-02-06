/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/06 09:22:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take the arg (char *) to look if it is a built-in or not. Return an int as
// a flag
int	is_built_in(char *cmd_arg)
{
	if ((ft_strncmp(cmd_arg, "echo", 4) == 0)
		|| (ft_strncmp(cmd_arg, "cd", 2) == 0)
		|| (ft_strncmp(cmd_arg, "env", 3) == 0)
		|| (ft_strncmp(cmd_arg, "exit", 4) == 0)
		|| (ft_strncmp(cmd_arg, "export", 6) == 0)
		|| (ft_strncmp(cmd_arg, "pwd", 3) == 0)
		|| (ft_strncmp(cmd_arg, "unset", 5) == 0))
		return (0); //need to double check as in pre_exec is set to false and true
	else
		return (1);
}

// Return nothing. Execute the correct built-in called. Take t_cmd to check
// the built-in received.
void	execute_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_args[0], "echo", 4) == 0)
		do_echo(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0)
		change_dir(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "env", 3) == 0)
		get_env();
	else if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
		write(STDERR_FILENO, "Builtin Error : How did exit() get here???\n", 43);
	else if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
		do_export(cmd);
	else if (ft_strncmp(cmd->cmd_args[0], "pwd", 3) == 0)
		get_pwd();
	else if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
		do_unset(cmd);
}

void	built_ins_childable(t_cmd *cmd) //il mettre exit, unset, cd et export
{
	if (ft_strncmp(cmd->cmd_args[0], "exit", 4) == 0)
	{
		close_fds(cmd);
		do_exit(cmd);
	}
	if (ft_strncmp(cmd->cmd_args[0], "unset", 5) == 0)
	{
		close_fds(cmd);
		do_unset(cmd);
	}
	if (ft_strncmp(cmd->cmd_args[0], "cd", 2) == 0)
	{
		close_fds(cmd);
		change_dir(cmd);
	}
	if (ft_strncmp(cmd->cmd_args[0], "export", 6) == 0)
	{
		close_fds(cmd);
		do_export(cmd);
	}
	else
		
}