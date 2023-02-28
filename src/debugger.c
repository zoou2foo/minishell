/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:27:18 by llord             #+#    #+#             */
/*   Updated: 2023/02/28 11:40:07 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints a gievn token lists according to internal specifications
void	print_token_list(t_token *head, bool start_with_newline)
{
	bool	show_joined = true;
	bool	show_newline = false;
	bool	show_content = true;
	bool	show_types = false;
	t_token	*node;

	node = head;
	if (start_with_newline)
		printf("\n");
	if (!show_newline)
		printf("|");
	while (node)
	{
		if (node && show_joined && node->is_joined)
			printf("__");
		else if (show_newline)
			printf("\n| ");
		else
			printf(" ");

		if (node->type == TTYPE_ERROR)
			printf("_ERROR_");
		else if (node->type == TTYPE_EMPTY)
			printf("_EMPTY_");
		else if (node->type && node->string)
		{
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
		}
		node = node->next;
	}
	printf("\n");
}

//prints a given command
void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("\n _COMMAND_#%i_\n|\n", cmd->id);

	printf("| fdin  : %i\n", cmd->fdin);
	printf("| fdout : %i\n|\n", cmd->fdout);

	printf("|\n|  _cmd_args_\n| |\n");
	i = -1;
	while (cmd->cmd_args[++i])
		printf("| | %i : '%s'\n", i, cmd->cmd_args[i]);
}

//prints a given string array
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	printf("\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

//runs minishell in debug mode (for minishell_tester)
void	minitest(char **av)
{
	init_meta();

	g_meta->state = MSTATE_NORMAL;
	g_meta->buf = ft_strdup(av[2]);
	if (!is_line_empty(g_meta->buf))
	{
		add_history(g_meta->buf);
		load_cmd_block(parse_line(g_meta->buf));
		if (g_meta->state == MSTATE_NORMAL)
			execute_cmd_block();
	}
	ft_free_null(g_meta->buf);

	clear_history();
	free_all();
	exit(g_meta->exit_status);
}

/*
//shows the conversions steps according to internal specifications
int	main(void)
{
	bool	show_env = false;
	bool	show_tokens = false;
	bool	show_cmds = true;

	int		i;

	char	*line = "<<END <\"$HOME\"/infile grep -v 42 \"\" | >> outfile wc -l > outfile2 | ls | \"\" \"\" >outfile3 | echo \"don't | $USER | split\"";
	//char	*line = "<$HOME/infile grep -v 42 "" "" | >> outfile wc -l > outfile2 | ls "" | >outfile3 | echo \"\"";
	//char	*line = "echo \"pew\" pew \"\"";
	//char	*line = "lol\"lol\"\'lol\'";
	//char	*line = "echo $USER $U $? $";

	printf("\n INPUT LINE : \"%s\"\n", line);

	init_meta();

	t_token	**token_block = parse_line(line);

	load_cmd_block(token_block);

	if (show_env)
	{
		print_tab_env();
	}

	if (show_tokens)
	{
		printf("\n");
		i = -1;
		while (token_block[++i])
			print_token_list(token_block[i], false);
		printf("\n\n");
	}

	if (show_cmds)
	{
		i = -1;
		while(g_meta->cmd_block[++i])
			print_cmd(g_meta->cmd_block[i]);
	}

	printf("\n");
}
*/