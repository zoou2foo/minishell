/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 13:57:47 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_data *data)
{
	
}

// COMMENT export seul: printf d'env en ajoutant "declare -x" avant chaque 
// COMMENT variable de env. Puis, chaque variable a été mis en ordre alpha
// COMMENT si on envoie export lol=haha, il faut qu'il soit ajouter à la liste
// COMMENT tu peux ajouter à la fin de la liste env.