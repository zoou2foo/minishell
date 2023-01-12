/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 15:33:42 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var

int	main(int ac, char **av)		//use char **environ instead
{

	(void)av;
	if (ac == 1)
	{
		t_cmd	*cmd = ft_calloc(sizeof(t_cmd), 1);
		cmd->cmd_args = ft_calloc(sizeof(char *), 3);
		cmd->cmd_args[0] = "cd";
		cmd->cmd_args[1] = "";

		init_meta();
		metadata->buf = readline("bash-Pew Pew> ");

		while (metadata->buf)
		{
			if (metadata->buf[0])
				add_history(metadata->buf);
			get_env();
			free(metadata->buf);
			metadata->buf = readline("bash-Pew Pew> ");
		}
		clear_history();
	}
	return (0);
}

//allocates memory for and fills the global metadata var with default values
void	init_meta(void)
{
	metadata = ft_calloc(sizeof(t_meta), 1);
	metadata->env = environ;			//I need to do a proper copy with malloc and strdup
	int	i;
	i = 0;
	while (environ[i])
		i++;
	metadata->env = ft_calloc(sizeof(char *), i);
	i = 0;
	while (environ[i])
	{
		metadata->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

// COMMENT if ac is not 1, error; void argv.
// COMMENT readline will malloc the char *buf, but it does NOT free it at the
// COMMENT end.

