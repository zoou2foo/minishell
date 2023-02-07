/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/02/07 13:48:05 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take t_cmd to look at the arg with export. Return an int as a flag.
int	check_arg_4_export(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_args[1] == NULL)
		return (1);
	return (-1);
}

// We could put this one in libft ⬇️
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// Take nothing; return nothing. Use global var to sort env in alpha order.
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

// Return the length of env. Take nothing as we use global var
int	env_length(void)
{
	int	i;

	i = 0;
	while (metadata->env[i])
		i++;
	return (i);
}

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

// Take t_cmd to check the arg of export. If no arg -> add declare -x and sort
// env. Else if arg -> add the var at metadata->env
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
		metadata->env = ft_recalloc(metadata->env, env_length() + 2, env_length() + 1, sizeof(char *)); //NEED to DEBUG here... maybe a prob of calloc
		while (metadata->env[i] != NULL)
			i++;
		metadata->env[i] = ft_strdup(cmd->cmd_args[1]);
		if (ft_strncmp(cmd->cmd_args[1], "PATH=", 5) == 0)
			refill_path_tab(cmd->cmd_args[1]);
	}
}
// vérifie si l'arg existe déjà dans env; si oui. free et réassigne. sinon, créer une nouvelle variable

void	reassign_var_env(t_cmd *cmd)
{
	int	len;
	int	i;
	
	while ()
}

// ft_strlen jusqu'à =.
// while (env[i])
//	ft_strncmp(str, env[i], len)
//		match -> replace
//		no match -> create new (normal)