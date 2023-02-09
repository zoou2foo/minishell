/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 14:12:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var

//prints the gien token lists according to internal specifications
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

	printf("| input  : %s\n", cmd->input);
	printf("| output : %s\n", cmd->output);

	printf("|\n|  _cmd_args_\n| |\n");
	i = -1;
	while (cmd->cmd_args[++i])
		printf("| | %i : '%s'\n",i, cmd->cmd_args[i]);
}

//prints metadata->env
void	print_tab_env(void)
{
	int	i;
	i = 0;
	printf("\n");
	while (metadata->env[i])
	{
		printf("%s\n", metadata->env[i]);
		i++;
	}
	printf("\n");
}

//checks if a given line contains either nothing or only space-like characters
int	is_line_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!is_space(line[i]))
			return (0);
	return (1);
}

//allocates memory for and fills the global metadata var with default values (for env and path)
void	init_meta(void)
{
	int	i;

	metadata = ft_calloc(sizeof(t_meta), 1);

	i = 0;
	while (environ[i])
		i++;
	metadata->env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (environ[i])
	{
		metadata->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

// Main logic loop of minishell. It initialises metadata and signals and every cycle, it:
// - reads the inputed line
// - checks if said line empty
// - add it to the history
// - converts it into a cmd_block
// - checks if the global state is still valid
// - execute said cmd_block
// - frees the line buffer
// - repeat
// Once the loop is over, it;
// - clears the history
// - frees all the leftover data
void	minishell(void)
{
	init_meta();
	init_signals(1);
	while (metadata->state >= 0)
	{
		metadata->state = MSTATE_NORMAL;
		metadata->buf = readline("MNSH > ");
		if (!metadata->buf)		//to make ctrl+d not segfault (cause it makes the buffer == null)
			break ;
		if (!is_line_empty(metadata->buf))
		{
			add_history(metadata->buf);
			load_cmd_block(parse_line(metadata->buf));
			if (metadata->state == MSTATE_NORMAL)
				execute_cmd_block();
			//free cmd_block & pipes
		}
		ft_free_null(metadata->buf);
	}
	clear_history();
	ft_free_null(metadata);		//FREE ALL SUB PARTS before (free_all()?)
}


int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)				//superfluous
		throw_error(ERR_AC);
	minishell();

	return (0);
}




//Loyc's main (DEBUG)


/*
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
		while(metadata->cmd_block[++i])
			print_cmd(metadata->cmd_block[i]);
	}

	printf("\n");
}
*/



//VAL's main (DEBUG)


/*
int	main(void)
{
	char	*line = "<<END <$HOME/infile grep -v 42 | >> outfile wc -l > outfile2 | ls | >outfile3 | echo \"don't | $USER | split\"";

	t_token	**token_array;
	t_cmd	*cmd;
	token_array = parse_line(line);

	t_token	*head;
	int		i;

	i = -1;
	printf("\n");
	while (token_array[++i])
	{
		head = token_array[i];
		print_token_list(head);
	}
	printf("\n");
	init_meta();
	// fill_path_tab();
	// i = 0;
	// while (metadata->path[i])
	// {
	// 	printf("%s\n", metadata->path[i]);
	// 	i++;
	// }
	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd_args = ft_calloc(sizeof(char *), 3);
	cmd->cmd_args[0] = "exit";
	cmd->cmd_args[1] = "42";
	do_exit(cmd);
	//find_cmd(cmd);
	return (0);
}
*/
