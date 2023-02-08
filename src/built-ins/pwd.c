/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:25:49 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 11:31:31 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Just use global var. Send back the path where the user is.
void	get_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		throw_error(ERR_PWD);
	}
	else
		printf("%s\n", cwd);
	exit (EXIT_SUCCESS);
}
