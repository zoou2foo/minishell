/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 08:52:54 by vjean             #+#    #+#             */
/*   Updated: 2023/01/25 11:53:15 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_cmd *cmd)
{
	printf("%s\n", cmd->cmd_args[1]);

}

// COMMENT si arg type-> normal: printf arg.
// COMMENT				 s_quote: printf arg (sans quote)
// COMMENT				 d_quote: printf arg AVEC expansion, si expansion dedans (sans quote)
// COMMENT				 expansion: prinft l'expansion de l'arg
// Déjà fait dans la tokenization; alors, on peut juste faire printf... à vérifier
