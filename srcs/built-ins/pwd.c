/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:25:49 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 12:49:17 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(t_data *data)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(2, "getcwd error", 12);
		exit (1);
	}
	else
		printf("%s\n", cwd);
}

//TODO need to add error message if the getcwd didn't work 