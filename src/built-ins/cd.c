/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 11:12:50 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take t_cmd to execute the cmd. Return nothing. EXECUTE: cd
void	change_dir(t_cmd *cmd)
{
	if (chdir(cmd->cmd_args[1]) != 0)
		write(2, "Error: no such file or directory", 32); //maybe define ERROR_MESS
	metadata->exit_status = EXIT_FAILURE;
}
