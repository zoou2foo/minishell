/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 13:44:25 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the given arg is a built-in
bool	is_built_in(char *arg)
{
	if (is_same(arg, "cd")
		|| is_same(arg, "echo")
		|| is_same(arg, "env")
		|| is_same(arg, "exit")
		|| is_same(arg, "export")
		|| is_same(arg, "pwd")
		|| is_same(arg, "unset"))
		return (true);
	else
		return (false);
}

// Executes the built-in called via the first cmd_arg
void	execute_builtins(t_cmd *cmd)
{
	char	*arg;

	close_fds(cmd);
	arg = cmd->cmd_args[0];
	if (is_same(arg, "cd"))
		change_dir(cmd);
	else if (is_same(arg, "echo"))
		do_echo(cmd);
	else if (is_same(arg, "env"))
		get_env();
	else if (is_same(arg, "exit"))
		do_exit(cmd);
	else if (is_same(arg, "export"))
		do_export(cmd);
	else if (is_same(arg, "pwd"))
		get_pwd();
	else if (is_same(arg, "unset"))
		do_unset(cmd);
}

// Checks if the built-in should be executed in a child process via the
// first cmd_arg
bool	built_ins_childable(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->cmd_args[0];
	if (is_same(arg, "cd")
		|| is_same(arg, "exit")
		|| is_same(arg, "unset"))
		return (false);
	else
		return (true);
}
