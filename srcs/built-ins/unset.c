/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 10:31:45 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_meta *metadata)
{

}

// COMMENT passe ligne par ligne metadata->envp pour faire un strdup et vérifier
// COMMENT si c'est égal à l'argument reçu avec unset. Si oui, on skip
// COMMENT puis renvoie cette nouvelle copie. ** il faut checker ce qu'on
// COMMENT reçoit comme argument.