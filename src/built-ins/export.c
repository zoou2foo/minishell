/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 14:24:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(void)
{

}

// COMMENT export seul: printf d'env en ajoutant "declare -x" avant chaque
// COMMENT variable de env. Puis, chaque variable a été mis en ordre alpha
// COMMENT si on envoie export lol=haha, il faut qu'il soit ajouter à la liste
// COMMENT tu peux ajouter à la fin de la liste env.