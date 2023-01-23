/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/01/18 10:57:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_cmd *cmd)
{
	char	**new_env;
	int		i;
	int		j;

	if (check_arg_4_unset(cmd) == 1)
	{
		i = 0;
		j = 0;
		while (metadata->env[i])
			i++;
		new_env = ft_calloc(sizeof(char *), i);
		i = 0;
		while (metadata->env[i])
		{
			if (ft_strncmp(cmd->cmd_args[1], metadata->env[i],
					ft_strlen(cmd->cmd_args[1]) == 0))
			{
				free(metadata->env[i]);
				i++;
			}
			else
			{
				new_env[j] = metadata->env[i];
				j++;
				i++;
			}
		}
	}
	else if (check_arg_4_unset(cmd) != 1)
	{
		printf("error: variable does not exist");
		exit (1);
	}
}

int	check_arg_4_unset(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (metadata->env[i])
	{
		if (ft_strncmp(cmd->cmd_args[1], metadata->env[i],
				ft_strlen(cmd->cmd_args[1])) == 0)
			return (1);
		else if (ft_strncmp(cmd->cmd_args[1], metadata->env[i],
				ft_strlen(cmd->cmd_args[1])) != 0)
			return (-1);
		i++;
	}
	return (0);
}

// COMMENT passe ligne par ligne metadata->envp pour faire un strdup et vérifier
// COMMENT si c'est égal à l'argument reçu avec unset. Si oui, on skip
// COMMENT puis renvoie cette nouvelle copie. ** il faut checker ce qu'on
// COMMENT reçoit comme argument.