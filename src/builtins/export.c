/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:09:31 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//uses sorts a g_meta->env in alphabetical order
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

//either adds or replaces a given ENV variable
void	add_var_to_env(char *var, int i)
{
	int	j;

	j = find_var(var);
	if (j >= 0)
	{
		ft_free_null(g_meta->env[j]);
		g_meta->env[j] = ft_strdup(var);
	}
	else
	{
		j = 0;
		while (g_meta->env[j])
		j++;
		g_meta->env = ft_recalloc(g_meta->env, j + 2, j + 1, sizeof(char *));
		while (g_meta->env[i] != NULL)
			i++;
		g_meta->env[i] = ft_strdup(var);
	}
}

//checks if the cmd->args are valid and adds them to g_meta->env
void	before_add_var(t_cmd *cmd, int i)
{
	int	k;

	k = 0;
	while (cmd->cmd_args[++k])
	{
		if (is_valid_name(cmd->cmd_args[k]))
			add_var_to_env(cmd->cmd_args[k], i);
		else
		{
			throw_error(ERR_ARG2);
			g_meta->exit_status = EXIT_FAILURE;
			break ;
		}
	}
}

//either sorts and print the g_meta->env OR add/replace an ENV var
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
		free_cmd_block();
		exit(EXIT_SUCCESS);
	}
	else
		before_add_var(cmd, i);
}
