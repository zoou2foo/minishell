/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 13:17:17 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data *data)
{
	if (chdir(argument) != 0)
	{
		write(2, "Error: no such file or directory: argument", 42);
		exit (1);
	}
}

// TODO need info from prompt
// TODO avant de chdir -> getcwd qui devient oldpwd dans env
// TODO je fais chdir et gestion d'erreur
// TODO refait getcwd qui devient mon actuel pwd dans env