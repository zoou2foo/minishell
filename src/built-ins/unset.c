/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:23:56 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 11:13:27 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_path_tab(void)
{
	int	i;

	i = 0;
	while (metadata->paths[i])
	{
		ft_free_null(metadata->paths[i]);
		i++;
	}
}


//return nothing. Take t_cmd to check what needs to be unset/free.
void	do_unset(t_cmd *cmd)
{
	char	**new_env;
	int		i;
	int		j;

	if (check_arg_4_unset(cmd) == 1)
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
		if (ft_strncmp(cmd->cmd_args[1], "PATH=", ft_strlen(cmd->cmd_args[1])) == 0)
			empty_path_tab();
		ft_free_null(metadata->env);
		metadata->env = new_env;
	}
	else if (check_arg_4_unset(cmd) != 1)
	{
		printf("error: variable does not exist\n"); //si variable n'existe pas, fait rien. New prompt. exit status 0
	}
	metadata->exit_status = EXIT_SUCCESS;
}

// Return int as a flag to know that it found the var in env. Take t_cmd of arg
int	check_arg_4_unset(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (metadata->env[i] != NULL)
	{
		if (ft_strncmp(cmd->cmd_args[1], metadata->env[i],
				ft_strlen(cmd->cmd_args[1])) == 0)
			return (1);
		i++;
	}
	return (-1);
}

