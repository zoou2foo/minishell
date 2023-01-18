/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/18 16:07:49 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var
/*
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
*/
// COMMENT if ac is not 1, error; void argv.
// COMMENT readline will malloc the char *buf, but it does NOT free it at the end.


//Loyc's main (DEBUG)

int	main(void)
{
	char	*line = "<<END <$HOMEinfile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | split\"";
	//char	*line = "lol \"L O L\"lol\'L O L\'lol";
	t_token	*node;

	printf("Tokenizing Line...\n");
	node = tokenize_input(line);
	printf("Printing Tokens...\n");
	while (node)
	{
		if (3 < node->type)
			printf("T%i", node->type);
		/*
		if (node->type == 4)
			printf("<");
		else if (node->type == 5)
			printf("<<");
		else if (node->type == 6)
			printf(">");
		else if (node->type == 7)
			printf(">>");
		else if (node->type == 8)
			printf("|");
		*/
		else
			printf("%s", node->string);
		node = node->next;
		printf(" : ");
		if (node && node->is_after_space)
			printf("__");
	}
	printf("\n");
}
