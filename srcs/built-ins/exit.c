/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:41:02 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 15:58:23 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_data *data)
{
	
}

// COMMENT if exit has an argument, it has to be a digit/number
// COMMENT after exit is done, do echo $? in the terminal to check the
// COMMENT argument passed; the digit sent.
// COMMENT need to keep a variable in the struct with the last exit status and
// COMMENT $? is a variable that represents the exit status
// COMMENT expansion est changer les variables d'env en leur valeur