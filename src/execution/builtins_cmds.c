/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 13:10:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if a given arg is on of the builtins
bool	is_built_in(char *arg)
{
	if (is_same(arg, "cd", true)
		|| is_same(arg, "echo", true)
		|| is_same(arg, "env", true)
		|| is_same(arg, "exit", true)
		|| is_same(arg, "export", true)
		|| is_same(arg, "pwd", true)
		|| is_same(arg, "unset", true))
		return (true);
	else
		return (false);
}

//executes the builtin in cmd->args[0]
void	execute_builtins(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->cmd_args[0];
	if (is_same(arg, "cd", true))
		change_dir(cmd);
	else if (is_same(arg, "echo", true))
		do_echo(cmd);
	else if (is_same(arg, "env", true))
		get_env();
	else if (is_same(arg, "exit", true))
		do_exit(cmd);
	else if (is_same(arg, "export", true))
		do_export(cmd);
	else if (is_same(arg, "pwd", true))
		get_pwd();
	else if (is_same(arg, "unset", true))
		do_unset(cmd);
}

//checks if the cmd->args[0] cmd should be done in a child
bool	is_childable(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->cmd_args[0];
	if (is_same(arg, "echo", true)
		|| is_same(arg, "env", true)
		|| is_same(arg, "export", true)
		|| is_same(arg, "pwd", true))
		return (true);
	else
		return (false);
}
