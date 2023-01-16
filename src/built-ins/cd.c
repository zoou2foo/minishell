/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2023/01/16 13:13:03 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_cmd_block *cmd)
{
	if (chdir(cmd->cmd_args[1]) != 0)		//placeholder variable FIXED
	{
		write(2, "Error: no such file or directory", 32);
		exit (1);
	}
}

// TODO call export to have pwd change in env.
// COMMENT relatif: ../Desktop. absolu: /usr/vjean/Desktop/