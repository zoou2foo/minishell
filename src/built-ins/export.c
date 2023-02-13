/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 09:30:35 by vjean            ###   ########.fr       */
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
	while (metadata->env[i])
	{
		if (ft_strncmp(cmd->cmd_args[1], metadata->env[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

//function to shortent do_export. It takes t_cmd and index to add a variable
//to env
// add var at the end of metadata->env with the arg
//set exit_status directly because non-childable when has args
void	add_var_to_env(t_cmd *cmd, int i)
{
	int	j;

	j = find_var(cmd);
	if (j >= 0)
	{
		reassign_var(j, cmd);
	}
	else
	{
		metadata->env = ft_recalloc(metadata->env, env_length() + 2,
			env_length() + 1, sizeof(char *)); //NEED to DEBUG here... maybe a prob of calloc
		while (metadata->env[i] != NULL)
			i++;
		metadata->env[i] = ft_strdup(cmd->cmd_args[1]);
	}
	metadata->exit_status = EXIT_SUCCESS;
}

// Take t_cmd to check the arg of export. If no arg -> add declare -x and sort
// env. Else if arg -> add the var at metadata->env (see ft above)l;
//set exit_status indirectly because childable when no args
void	do_export(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd->cmd_args[1] == NULL)
	{
		sort_env();
		while (metadata->env[i] != NULL)
		{
			printf("declare -x ");
			printf("%s\n", metadata->env[i]);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	else
		add_var_to_env(cmd, i);
}


