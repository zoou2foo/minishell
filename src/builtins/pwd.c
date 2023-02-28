/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:25:49 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 11:04:25 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints the current location (user path)
void	get_pwd(void)
{
	char	cwd[1000];

	free_cmd_block();
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		throw_error(ERR_PWD);
		exit (EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", cwd);
		exit (EXIT_SUCCESS);
	}
}
