/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/16 15:02:01 by llord            ###   ########.fr       */
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
			if (ft_strncmp(metadata->buf, "env", 4) == 0)
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
	int	i;

	metadata = ft_calloc(sizeof(t_meta), 1);
	metadata->env = environ;
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
<<<<<<< HEAD
// COMMENT end.


//Loyc's main (DEBUG)
/*
int	main(void)
{
	char	*line = "hellow world! | sup?";
	t_cmd_block	*cmdblock;
	cmdblock = parse_line(line);
	printf("%s\n", cmdblock->cmds[0]->cmd_args[0]);
	printf("%s\n", cmdblock->cmds[0]->cmd_args[0]);
}
*/
=======
// COMMENT end.
>>>>>>> f3dba17960b8d81900fe3bf3c0a1ed8744168b6d
