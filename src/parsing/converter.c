/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/26 16:11:42 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	from token array

	create one t_cmd per line

	loop on all lines multiple times:
		- once to merge tokens (ex > type + string = string w/ type >)
		- once to fill teh t_cmd with the redir (and call here*
		10
		doc funct)
		- once to convert remaining tokens into cmd_args

	free all tokens

	//AFTER WE SHOULD TEST/INTEGRATE THE BUILT-INS

*/

t_cmd	*convert(t_token *head)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));





	return (cmd);
}