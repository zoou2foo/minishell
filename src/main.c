/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/24 14:45:57 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var

int	main(int ac, char **av)		//use char **environ instead
{
	//extern	char	**environ; //pas de variable globale
	(void)av;
	if (ac == 1)
	{
		t_cmd	*cmd = ft_calloc(sizeof(t_cmd), 1);
		cmd->cmd_args = ft_calloc(sizeof(char *), 3);
		cmd->cmd_args[0] = "cd";
		cmd->cmd_args[1] = "/Users/vjean/Desktop/pipex/srcs";
		init_meta();
		metadata->buf = readline("bash-Pew Pew> ");
		while (metadata->buf)
		{
			if (metadata->buf[0])
				add_history(metadata->buf);
			if (ft_strncmp(metadata->buf, "cd", 2) == 0)
				change_dir(cmd);
			if (ft_strncmp(metadata->buf, "pwd", 2) == 0)
				get_pwd();
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
	metadata->env[i] = NULL;
}

// COMMENT if ac is not 1, error; void argv.
// COMMENT readline will malloc the char *buf, but it does NOT free it at
// COMMENT the end.
//VAL's main (DEBUG)

// int	main(void)
// {
// 	init_meta();
// 	fill_path_tab();

// }

// int	main(void)
// {
// 	char	*line = "<<END <$HOME/infile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | $USER | split\"";

// 	t_token	**token_array;
// 	t_cmd	*cmd;
// 	token_array = parse_line(line);

// 	t_token	*head;
// 	int		i;

// 	i = -1;
// 	printf("\n");
// 	while (token_array[++i])
// 	{
// 		head = token_array[i];
// 		print_token_list(head);
// 	}
// 	printf("\n");
// 	init_meta();
// 	// fill_path_tab();
// 	// i = 0;
// 	// while (metadata->path[i])
// 	// {
// 	// 	printf("%s\n", metadata->path[i]);
// 	// 	i++;
// 	// }
// 	cmd = ft_calloc(sizeof(t_cmd), 1);
// 	cmd->cmd_args = ft_calloc(sizeof(char *), 3);
// 	cmd->cmd_args[0] = "exit";
// 	cmd->cmd_args[1] = "42";
// 	do_exit(cmd);
// 	//find_cmd(cmd);
// 	return (0);
// }


//Loyc's main (DEBUG)

void	print_token_list(t_token *head)
{
	bool	show_joined = true;
	bool	show_newline = false;
	bool	show_content = true;
	bool	show_types = false;

	t_token	*node;

	node = head;
	if (!show_newline)
		printf("\n");
	while (node)
	{
		if (node && show_joined && node->is_joined)
				printf("__");
		else if (show_newline)
			printf("\n");
		else
			printf(" ");

		if (node->type < 5)
		{
			if (show_content)
				printf("%s", node->string);
			else if (node->type == 1)
				printf("string");
			else if (node->type == 2)
				printf("\'string\'");
			else if (node->type == 3)
				printf("\"string\"");
			else if (node->type == 4)
				printf("$EXPAND");
		}
		else
		{
			if (show_types)
				printf("_T%i_", node->type);
			else if (node->type == 5)
				printf("<");
			else if (node->type == 6)
				printf("<<");
			else if (node->type == 7)
				printf(">");
			else if (node->type == 8)
				printf(">>");
			else if (node->type == 9)
				printf("|");
		}
		node = node->next;
	}
	printf("\n");
}
/*
int	main(void)
{

	char	*line = "<<END <$HOME/infile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | $USER | split\"";
	//char	*line = "lol\"LOL\"\"lol\"lol\'LOL\'lol";
	//char	*line = "lol\"lol\"\'lol\'";
	//har	*line = "$USER$USER";

	t_token	*head;

 	printf("\n\nTokenizing Line...\n\n");
 	head = create_token_list(line);
	print_token_list(head);

 	printf("\n\nExpanding Tokens...\n\n");
 	expand_token_list(head);
	print_token_list(head);

 	printf("\n\nMerging Tokens...\n\n");
 	head = merge_token_list(head);
	print_token_list(head);

	printf("\n\n");
}
*/


// int	main(void)
// {
// 	//char	*line = "<<END <$HOME/infile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | $USER | split\"";
// 	//char	*line = "lol\"LOL\"\"lol\"lol\'LOL\'lol";
// 	//char	*line = "lol\"lol\"\'lol\'";
// 	//har	*line = "$USER$USER";
// 	char	*line = "cat file1";

// 	t_token	**token_array;
// 	token_array = parse_line(line);

// 	t_token	*head;
// 	int		i;

// 	i = -1;
// 	printf("\n");
// 	while(token_array[++i])
// 	{
// 		head = token_array[i];
// 		print_token_list(head);
// 	}
// 	fill_path_tab();
// 	//find_cmd(token_array);
// 	printf("\n");
// }
