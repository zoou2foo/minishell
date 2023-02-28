/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 11:15:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if a given arg is on of the builtins
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

//executes the builtin in cmd->args[0]
void	execute_builtins(t_cmd *cmd)
{
	char	*arg;

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

//checks if the cmd->args[0] cmd should be done in a child
bool	is_childable(t_cmd *cmd)
{
	char	*arg;

	arg = cmd->cmd_args[0];
	if (is_same(arg, "echo")
		|| is_same(arg, "env")
		|| is_same(arg, "export")
		|| is_same(arg, "pwd"))
		return (true);
	else
		return (false);
}
