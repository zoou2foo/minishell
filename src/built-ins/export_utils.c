/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:18:24 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 12:24:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
void	refill_path_tab(char *str)
{
	int		i;
	char	*tmp;

	g_meta->paths = ft_split(&str[5], ':');
	i = 0;

	while (g_meta->paths[i])
	{
		tmp = ft_strjoin(g_meta->paths[i], "/"); //adds final / so we don't have to during excecution
		ft_free_null(g_meta->paths[i]);
		g_meta->paths[i] = tmp;
		i++;
	}
	return ;
}

void	reassign_var(int j, t_cmd *cmd)
{
	ft_free_null(g_meta->env[j]);
	g_meta->env[j] = ft_strdup(cmd->cmd_args[1]);
}