/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 15:18:18 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take nothing; return nothing. Use global var to sort env in alpha order.
void	sort_env(void)
{
	char	*tmp;
	int		i;
	int		j;
	int		j_min;

	i = 0;
	while (g_meta->env[i])
	{
		j = i + 1;
		j_min = i;
		while (g_meta->env[j])
		{
			if (ft_strcmp(g_meta->env[j], g_meta->env[j_min]) < 0)
				j_min = j;
			j++;
		}
		if (j_min != i)
		{
			tmp = g_meta->env[i];
			g_meta->env[i] = g_meta->env[j_min];
			g_meta->env[j_min] = tmp;
		}
		i++;
	}
}

// Return the length of env. Take nothing as we use global var
int	env_length(void)
{
	int	i;

	i = 0;
	while (g_meta->env[i])
		i++;
	return (i);
}

//if not found, return -1
//to check if var exist already
int	find_var(t_cmd *cmd)
{
	int	len;
	int	i;

	len = 0;
	while (cmd->cmd_args[1][len] && cmd->cmd_args[1][len] != '=')
		len++;
	i = 0;
	while (g_meta->env[i])
	{
		if (ft_strncmp(cmd->cmd_args[1], g_meta->env[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//function to shortent do_export. It takes t_cmd and index to add a variable
//to env
// add var at the end of g_meta->env with the arg
//set exit_status directly because non-childable when has args
void	add_var_to_env(t_cmd *cmd, int j, int i)
{
	if (j >= 0)
	{
		reassign_var(j, cmd);
	}
	else
	{
		g_meta->env = ft_recalloc(g_meta->env, env_length() + 2,
				env_length() + 1, sizeof(char *));
		while (g_meta->env[i] != NULL)
			i++;
		g_meta->env[i] = ft_strdup(cmd->cmd_args[1]);
	}
	g_meta->exit_status = EXIT_SUCCESS;
}

// Take t_cmd to check the arg of export. If no arg -> add declare -x and sort
// env. Else if arg -> add the var at g_meta->env (see ft above)l;
//set exit_status indirectly because childable when no args
void	do_export(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd->cmd_args[1] == NULL)
	{
		sort_env();
		while (g_meta->env[i] != NULL)
		{
			printf("declare -x ");
			printf("%s\n", g_meta->env[i]);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		j = find_var(cmd);
		add_var_to_env(cmd, j, i);
	}
}
