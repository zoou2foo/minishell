/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 15:31:17 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_data *data)
{
	
}

// COMMENT passe ligne par ligne data->envp pour faire un strdup et vérifier
// COMMENT si c'est égal à l'argument reçu avec unset. Si oui, on skip
// COMMENT puis renvoie cette nouvelle copie. ** il faut checker ce qu'on 
// COMMENT reçoit comme argument.