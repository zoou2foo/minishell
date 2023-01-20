/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/20 12:36:23 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var
/*
int	main(int ac, char **av)		//use char **environ instead
{
	//extern	char	**environ; //pas de variable globale
	(void)av;
	if (ac == 1)
	{
		t_cmd	*cmd = ft_calloc(sizeof(t_cmd), 1);
		cmd->cmd_args = ft_calloc(sizeof(char *), 3);
		cmd->cmd_args[1] = "PATH";
		init_meta();
		metadata->buf = readline("bash-Pew Pew> ");
		while (metadata->buf)
		{
			if (metadata->buf[0])
				add_history(metadata->buf);
			if (ft_strncmp(metadata->buf, "env", 3) == 0)
				geclet_env();
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
	//metadata->env = environ; //je refais exactement ça avec strdup;
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

//VAL's main (DEBUG)
int	main(void)
{
	char	*str = "bla $LANG bla $USER";

	printf("%s\n", do_expand_in_dbl_quotes(str));
	return (0);
}


//Loyc's main (DEBUG)

// int	main(void)
// {
// 	bool	show_joined = true;
// 	bool	show_newline = true;
// 	bool	show_content = true;
// 	bool	show_types = false;

// 	char	*line = "<<END <$HOMEinfile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | split\"";
// 	//char	*line = "lol \"L O L\"\"lol\"lol\'L O L\'lol";
// 	//char	*line = "\"s\"p\'l\'";
// 	//char	*line = "$USER$USER";

// 	t_token	*node;

// // 	printf("Tokenizing Line...\n");
// // 	node = tokenize_input(line);
// // 	printf("Printing Tokens...\n\n");

// 	while (node)
// 	{
// 		if (node && show_joined && node->is_joined)
// 				printf("__");
// 		else if (show_newline)
// 			printf("\n");
// 		else
// 			printf(" ");

// 		if (node->type < 5)
// 		{
// 			if (show_content)
// 				printf("%s", node->string);
// 			else if (node->type == 1)
// 				printf("string");
// 			else if (node->type == 2)
// 				printf("\'string\'");
// 			else if (node->type == 3)
// 				printf("\"string\"");
// 			else if (node->type == 4)
// 				printf("$EXPAND");
// 		}
// 		else
// 		{
// 			if (show_types)
// 				printf("_T%i_", node->type);
// 			else if (node->type == 5)
// 				printf("<");
// 			else if (node->type == 6)
// 				printf("<<");
// 			else if (node->type == 7)
// 				printf(">");
// 			else if (node->type == 8)
// 				printf(">>");
// 			else if (node->type == 9)
// 				printf("|");
// 		}
// 		node = node->next;
// 	}
// 	printf("\n\n");
// }
