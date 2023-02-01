/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:39:03 by vjean             #+#    #+#             */
/*   Updated: 2023/02/01 11:48:48 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_or_builtins(t_cmd *cmd)
{
	metadata->cmd_path = find_cmd(cmd);
	if (metadata->cmd_path)
		return (2) //flag to indicate that we have a sys_cmd
	else //or better to do a ft_strcmp of cmd_args and any of the built-in...
		return (3) //flag to indicate that we have a built-ins
}