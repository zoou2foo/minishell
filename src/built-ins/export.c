/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/01/26 15:01:36 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_4_export(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_args[1] == NULL)
		return (1);
	return (-1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	sort_env(void)
{
	char	*tmp;
	int		i;
	int		j;
	int		j_min;

	i = 0;
	while (metadata->env[i])
	{
		j = i + 1;
		j_min = i;
		while (metadata->env[j])
		{
			if (ft_strcmp(metadata->env[j], metadata->env[j_min]) < 0)
				j_min = j;
			j++;
		}
		if (j_min != i)
		{
			tmp = metadata->env[i];
			metadata->env[i] = metadata->env[j_min];
			metadata->env[j_min] = tmp;
		}
		i++;
	}
}

int	env_length()
{
	int	i;

	i = 0;
	while (metadata->env[i])
		i++;
	return (i);
}

void	do_export(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (check_arg_4_export(cmd) == 1)
	{
		sort_env();
		while (metadata->env[i] != NULL)
		{
			printf("declare -x ");
			printf("%s\n", metadata->env[i]);
			i++;
		}
	}
	else if (check_arg_4_export(cmd) != 1)
	{
		// ajoute la variable à la fin de metadata->env avec l'arg.
		metadata->env = ft_recalloc(metadata->env, env_length() + 2, env_length() + 1, sizeof(char *));
		while (metadata->env[i] != NULL)
			i++;
		metadata->env[i] = ft_strdup(cmd->cmd_args[1]);
	}
}

// COMMENT export seul: printf d'env en ajoutant "declare -x" avant chaque
// COMMENT variable de env. Puis, chaque variable a été mis en ordre alpha
// COMMENT si on envoie export lol=haha, il faut qu'il soit ajouter à la liste
// COMMENT tu peux ajouter à la fin de la liste env.