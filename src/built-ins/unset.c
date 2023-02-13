/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 14:56:38 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns 1 if the env variable exists
bool	is_var_in_env(char *var)
{
	int	i;

	i = 0;
	if (var)
	{
		while (g_meta->env[i] != NULL)
		{
			if (ft_strncmp(var, g_meta->env[i], ft_strlen(var)) == 0)
				return (true);
			i++;
		}
	}
	return (false);
}

//look at the arg sent; to free the line in env. Then, create a new env
//without the one sent in arg
// void	shorten_unset_arg(t_cmd *cmd, char **new_env, int i, int j)
// {
// 	if (ft_strncmp(cmd->cmd_args[1], g_meta->env[i],
// 			ft_strlen(cmd->cmd_args[1])) == 0) //besoin de mettre à 1
// 	{
// 		ft_free_null(g_meta->env[i]);
// 		i++;
// 	}
// 	else
// 	{
// 		new_env[j] = g_meta->env[i];
// 		j++;
// 		i++;
// 	}
// }

//setup a new_env to take out the var sent in arg
//Return nothing. Take t_cmd to have access to the arg
// void	unset_arg(t_cmd *cmd)
// {
// 	char	**new_env;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (g_meta->env[i])
// 		i++;
// 	new_env = ft_calloc(i, sizeof(char *));
// 	i = 0;
// 	while (g_meta->env[i])
// 	{
// 		shorten_unset_arg(cmd, new_env, i, j);
// 	}
// 	ft_free_null(g_meta->env);
// 	g_meta->env = new_env;
// }

//return nothing. Take t_cmd to check what needs to be unset/free.
//final else, if the var does not exist
void	do_unset(t_cmd *cmd)
{
	char	**new_env;
	int		i;
	int		j;

	if (!cmd->cmd_args[1])
	{
		throw_error(ERR_ARG);
		g_meta->exit_status = EXIT_FAILURE;
	}
	else if (is_var_in_env(cmd->cmd_args[1]))
	{
		i = 0;
		j = 0;
		while (g_meta->env[i])
			i++;
		new_env = ft_calloc(i, sizeof(char *));
		i = 0;
		while (g_meta->env[i])
		{
			if (ft_strncmp(cmd->cmd_args[1], g_meta->env[i],
				ft_strlen(cmd->cmd_args[1])) == 0) //besoin de mettre à 1
			{
				ft_free_null(g_meta->env[i]);
				i++;
			}
			else
			{
				new_env[j] = g_meta->env[i];
				j++;
				i++;
			}
		}
		ft_free_null(g_meta->env);
		g_meta->env = new_env;
	}
	else // si variable n'existe pas
	{
		throw_error(ERR_ENV);
		g_meta->exit_status = EXIT_FAILURE;
	}
	g_meta->exit_status = EXIT_SUCCESS;
}
