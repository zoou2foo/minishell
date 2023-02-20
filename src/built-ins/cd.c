/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2023/02/20 08:35:00 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take t_cmd to execute the cmd. Return nothing. EXECUTE: cd through chdir()
void	change_dir(t_cmd *cmd)
{
	if (cmd->argcount < 2)
	{
		throw_error(ERR_ARG);
		g_meta->exit_status = EXIT_FAILURE;
	}
	else if (cmd->argcount > 2)
	{
		throw_error(ERR_ARG3);
		g_meta->exit_status = EXIT_FAILURE;
	}
	else if (chdir(cmd->cmd_args[1]) != 0)
	{
		throw_error(ERR_CD);
		g_meta->exit_status = EXIT_FAILURE;
	}
}
