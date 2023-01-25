/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/01/25 16:15:55 by vjean            ###   ########.fr       */
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

char	**sort_env(void)
{
	char	**new_env;
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = i + 1;
	size = array_len();
	new_env = ft_calloc(sizeof(char *), size + 1);
	while (i < size)
	{
		if (metadata->env[i] > metadata->env[j])
			j++;
		else
		{
			tmp = ft_strdup(metadata->env[i]);
			array_sorted(new_env, tmp, size);
			i = j;
			j++;
		}
	}
	return (new_env);
}

int	array_len(void)
{
	int	i;

	i = 0;
	while (metadata->env[i])
		i++;
	return (i);
}

void	array_sorted(char **new_env, char *tmp, int size)
{
	int	index;
	int	j;

	index = 1;
	j = 0;
	while (size > 0)
	{
		if (new_env[size] == NULL)
		{
			new_env[size] = ft_strdup(tmp);
			printf("new_env[%i] = %s\n", size, new_env[size]);
		}
		else if (check_double(new_env, tmp) == 1)
		{
			new_env[size - index] = ft_strdup(tmp);
			index++;
			size--;
		}
		else
			j++;
	}
}

int	check_double(char **new_env, char *tmp)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		if (ft_strncmp(new_env[i], tmp, ft_strlen(new_env[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}

// char	**sort_env(void)
// {
// 	char	**new_env;
// 	int		i;
// 	int		j;
// 	int		size;
// 	int		flag;

// 	size = 0;
// 	while (metadata->env[size])
// 		size++;
// 	new_env = ft_calloc(sizeof(char *), size + 1);
// 	i = 0;
// 	while (i < size)
// 	{
// 		flag = i;
// 		j = i + 1;
// 		while (j < size)
// 		{
// 			while ()
// 			{
// 				if (metadata->env[flag], metadata->env[j], ft_strlen(metadata->env[flag])) == 0)
// 					flag = j;
// 			}
// 			j++;
// 		}
// 		if (flag != i)
// 		{
// 			new_env[i] = ft_strdup(metadata->env[i]);
// 			metadata->env[i] = ft_strdup(metadata->env[flag]);
// 			metadata->env[flag] = ft_strdup(new_env[i]);
// 			//ft_strlcpy(new_env[i], metadata->env[i], ft_strlen(metadata->env[i]));
// 			//ft_strlcpy(metadata->env[i], metadata->env[flag], ft_strlen(metadata->env[flag]));
// 			//ft_strlcpy(metadata->env[flag], new_env[i], ft_strlen(new_env[i]));
// 		}
// 		i++;
// 	}
// }


// COMMENT export seul: printf d'env en ajoutant "declare -x" avant chaque
// COMMENT variable de env. Puis, chaque variable a été mis en ordre alpha
// COMMENT si on envoie export lol=haha, il faut qu'il soit ajouter à la liste
// COMMENT tu peux ajouter à la fin de la liste env.