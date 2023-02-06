/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:52:54 by vjean             #+#    #+#             */
/*   Updated: 2023/02/03 11:11:05 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return NOTHING. Take t_cmd; the argument following "echo" to be printed.
void	do_echo(t_cmd *cmd)
{
	printf("%s\n", cmd->cmd_args[1]);
}


// echo helloe motherfuckers --> only print hello