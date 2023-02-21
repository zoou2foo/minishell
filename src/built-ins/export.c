/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 13:34:53 by vjean            ###   ########.fr       */
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

//function to shortent export. It takes a string and an index. Return nothing
void	add_var_to_env(char *str, int i)
{
	int	j;

	j = find_var(str);
	if (j >= 0) //reassess the old var
	{
		ft_free_null(g_meta->env[j]);
		g_meta->env[j] = ft_strdup(str);
	}
	else // creates a new var
	{
		j = 0;
		while (g_meta->env[j])
		j++;
		g_meta->env = ft_recalloc(g_meta->env, j + 2, j + 1, sizeof(char *));
		while (g_meta->env[i] != NULL)
			i++;
		g_meta->env[i] = ft_strdup(str);
	}
}

//function to shorten export
//before adding var need the name of var to make sure it is valid.
//takes t_cmd *cmd to look at the arg and an index from do_export()
void	before_add_var(t_cmd *cmd, int i)
{
	int	k;

	k = 1;
	while (cmd->cmd_args[k])
	{
		if (is_valid_name(cmd->cmd_args[k]))
			add_var_to_env(cmd->cmd_args[k], i);
		else
		{
			throw_error(ERR_ARG2);
			g_meta->exit_status = EXIT_FAILURE;
			break ;
		}
		k++;
	}
}

// Take t_cmd to check the arg of export. If no arg -> add declare -x and sort
// env. Else if arg -> add the var at g_meta->env (see ft above)l;
//set exit_status indirectly because childable when no args
void	do_export(t_cmd *cmd)
{
	int		i;

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
		before_add_var(cmd, i);
	}
}
