/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 12:41:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_path_tab(void)		//obsolete
{
	int	i;

	i = 0;
	while (metadata->paths[i])
	{
		ft_free_null(metadata->paths[i]);
		i++;
	}
	ft_free_null(metadata->paths);
}

// returns 1 if the env variable exists
bool	is_var_in_env(char *var)
{
	int	i;

	i = 0;
	if (var)
	{
		while (metadata->env[i] != NULL)
		{
			if (ft_strncmp(var, metadata->env[i], ft_strlen(var)) == 0)
				return (true);
			i++;
		}
	}
	return (false);
}

//return nothing. Take t_cmd to check what needs to be unset/free.
void	do_unset(t_cmd *cmd)
{
	char	**new_env;
	int		i;
	int		j;

	if (!cmd->cmd_args[1])
	{
		throw_error(ERR_ARG);
		metadata->exit_status = EXIT_FAILURE;
	}
	else if (is_var_in_env(cmd->cmd_args[1]))
	{
		i = 0;
		j = 0;
		while (metadata->env[i])
			i++;
		new_env = ft_calloc(i, sizeof(char *));
		i = 0;
		while (metadata->env[i])
		{
			if (ft_strncmp(cmd->cmd_args[1], metadata->env[i],
				ft_strlen(cmd->cmd_args[1])) == 0) //besoin de mettre à 1
			{
				ft_free_null(metadata->env[i]);
				i++;
			}
			else
			{
				new_env[j] = metadata->env[i];
				j++;
				i++;
			}
		}
		ft_free_null(metadata->env);
		metadata->env = new_env;
	}
	else // si variable n'existe pas
	{
		throw_error(ERR_ENV);
		metadata->exit_status = EXIT_FAILURE;
	}
	metadata->exit_status = EXIT_SUCCESS;
}
