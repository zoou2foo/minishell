/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:44:44 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 11:52:25 by llord            ###   ########.fr       */
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

//to check if var exist already
//if not found, return -1
int	find_var(char *str)
{
	int	len;
	int	i;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	i = 0;
	while (g_meta->env[i])
	{
		if (ft_strncmp(g_meta->env[i], str, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	is_valid_name(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i > 0 && str[i] == '=')
		return (TRUE);
	return (FALSE);
}

//function to shortent do_export. It takes t_cmd and index to add a variable
//to env
//add var at the end of g_meta->env with the arg
//set exit_status directly because non-childable when has args
void	add_var_to_env(char *str, int i)
{
	int	j;

	j = find_var(str);
	if (j >= 0) //reassing old var
	{
		ft_free_null(g_meta->env[j]);
		g_meta->env[j] = ft_strdup(str);
	}
	else //creates new var
	{
		j = 1 + env_length();
		g_meta->env = ft_recalloc(g_meta->env, j + 1, j, sizeof(char *));
		while (g_meta->env[i] != NULL)
			i++;
		g_meta->env[i] = ft_strdup(str);
	}
}

// Take t_cmd to check the arg of export. If no arg -> add declare -x and sort
// env. Else if arg -> add the var at g_meta->env (see ft above)l;
//set exit_status indirectly because childable when no args
void	do_export(t_cmd *cmd)
{
	int		i;
	int		k;

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
}
