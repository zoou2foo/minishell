/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:18:24 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 10:47:57 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
void	refill_path_tab(char *str)
{
	int		i;
	char	*tmp;

	metadata->paths = ft_split(&str[5], ':');
	i = 0;

	while (metadata->paths[i])
	{
		tmp = ft_strjoin(metadata->paths[i], "/");		//adds final / so we don't have to during excecution
		ft_free_null(metadata->paths[i]);
		metadata->paths[i] = tmp;
		i++;
	}
	return ;
}

void	reassign_var(int j, t_cmd *cmd)
{
	ft_free_null(metadata->env[j]);
	metadata->env[j] = ft_strdup(cmd->cmd_args[1]);
}