/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:49:38 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 10:58:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_meta *metadata) //il ajouter t_cmd *cmd;
{
	char	dir[100];

	getcwd(dir, sizeof(dir));
	if (chdir(argument) != 0)		//placeholder variable (?) **cmd_args
	{
		write(2, "Error: no such file or directory: argument", 42);
		exit (1);
	}
	getcwd(dir, sizeof(dir));
}

// TODO need info from prompt
// TODO avant de chdir -> getcwd qui devient oldpwd dans env
// TODO je fais chdir et gestion d'erreur(file or directory does not exist)
// TODO refait getcwd qui devient mon actuel pwd dans env