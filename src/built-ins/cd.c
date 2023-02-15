/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 10:08:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take t_cmd to execute the cmd. Return nothing. EXECUTE: cd
void	change_dir(t_cmd *cmd)
{
	if (chdir(cmd->cmd_args[1]) != 0)
	{
		throw_error(ERR_CD);
		g_meta->exit_status = EXIT_FAILURE;
	}
}
