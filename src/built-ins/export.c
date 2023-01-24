/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/01/24 14:00:25 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_cmd *cmd)
{
	//char	**new_env;
	int		i;
	//int		j;

	i = 0;
	if (check_arg_4_export(cmd) == 1)
	{
		// printf declare -x et place in order
		while (metadata->env[i] != NULL)
		{
			printf("declare -x ");
			sort_env();
			printf("%s\n", metadata->env[i]);
		}
	}
	else if (check_arg_4_export(cmd) != 1)
	{
		// ajoute la variable à la fin de metadata->env avec l'arg.
		while (metadata->env[i] != NULL)
			i++;
		metadata->env[i] = cmd->cmd_args[1];
	}
}

int	check_arg_4_export(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_args[1] == NULL)
		return (1);
	return (-1);
}

void	sort_env(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (metadata->env[i] != NULL)
	{
		if (metadata->env[i] > metadata->env[i + 1])
		{
			tmp = metadata->env[i];
			metadata->env[i] = metadata->env[i + 1];
			metadata->env[i + 1] = tmp;
		}
		i++;
	}
}

// COMMENT export seul: printf d'env en ajoutant "declare -x" avant chaque
// COMMENT variable de env. Puis, chaque variable a été mis en ordre alpha
// COMMENT si on envoie export lol=haha, il faut qu'il soit ajouter à la liste
// COMMENT tu peux ajouter à la fin de la liste env.