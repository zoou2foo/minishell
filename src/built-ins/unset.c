/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 10:09:31 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 if the env variable exists
bool	is_var_in_env(char *var)
{
	int	i;

	i = 0;
	if (var)
	{
		while (g_meta->env[i] != NULL)
		{
			if (is_same(g_meta->env[i], var))
				return (true);
			i++;
		}
	}
	return (false);
}

//ft to shorten do_unset(). Unset the arg sent and create a new env
void	unset_arg(char *str)
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
		if (ft_strncmp(str, g_meta->env[i],
				ft_strlen(str)) == 0)
			ft_free_null(g_meta->env[i++]);
		else
			new_env[j++] = g_meta->env[i++];
	}
	ft_free_null(g_meta->env);
	g_meta->env = new_env;
}

//return nothing. Take t_cmd to check what needs to be unset/free.
//final else, if the var does not exist
void	do_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->cmd_args[1])
	{
		throw_error(ERR_ARG);
		g_meta->exit_status = EXIT_FAILURE;
	}
	while (cmd->cmd_args[i])
	{
		if (is_var_in_env(cmd->cmd_args[i]))
			unset_arg(cmd->cmd_args[i]);
		else
		{
			throw_error(ERR_ENV);
			g_meta->exit_status = EXIT_FAILURE;
		}
		i++;
	}
}
