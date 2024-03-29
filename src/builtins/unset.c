/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:18:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if a given var matches with g_meta->env[var_id]
bool	does_var_matches(char *var, int var_id)
{
	if (is_same(g_meta->env[var_id], var, false))
		if (g_meta->env[var_id][ft_strlen(var)] == '=')
			return (true);
	return (false);
}

//checks if the specified var is present in g_meta->env
bool	is_var_in_env(char *var)
{
	int	i;

	i = 0;
	if (var)
	{
		while (g_meta->env[i] != NULL)
		{
			if (does_var_matches(var, i))
				return (true);
			i++;
		}
	}
	return (false);
}

//recreates g_meta->env without the specific var
void	unset_arg(char *var)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_meta->env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	i = 0;
	while (g_meta->env[i])
	{
		if (does_var_matches(var, i))
			ft_free_null(g_meta->env[i++]);
		else
			new_env[j++] = g_meta->env[i++];
	}
	ft_free_null(g_meta->env);
	g_meta->env = new_env;
}

//removes the given cmd->args from g_meta->env if possible
void	do_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->argcount < 2)
	{
		throw_error(ERR_ARG);
		g_meta->exit_status = EXIT_FAILURE;
	}
	else
	{
		while (cmd->cmd_args[i])
		{
			if (is_var_in_env(cmd->cmd_args[i]))
				unset_arg(cmd->cmd_args[i]);
			else if (g_meta->exit_status == MSTATE_NORMAL)
			{
				throw_error(ERR_VAR);
				g_meta->exit_status = EXIT_FAILURE;
			}
			i++;
		}
	}
}
