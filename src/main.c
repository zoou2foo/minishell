/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/02/16 13:21:06 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*g_meta;	//our global var

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

	printf("|\n|  _cmd_args_\n| |\n");
	i = -1;
	while (cmd->cmd_args[++i])
		printf("| | %i : '%s'\n", i, cmd->cmd_args[i]);
}

//prints g_meta->env
void	print_tab_env(void)
{
	int	i;

	i = 0;
	printf("\n");
	while (g_meta->env[i])
	{
		printf("%s\n", g_meta->env[i]);
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
		if (!ft_isspace(line[i]))
			return (0);
	return (1);
}

//allocates memory for and fills the global g_meta var with default values (for env and path)
void	init_meta(void)
{
	int	i;

	g_meta = ft_calloc(sizeof(t_meta), 1);

	i = 0;
	while (environ[i])
		i++;
	g_meta->env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (environ[i])
	{
		g_meta->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->cmd_args && cmd->cmd_args[0])
		{
			i = -1;
			while (cmd->cmd_args[++i])
				ft_free_null(cmd->cmd_args[i]);
		}
		if (cmd->fdin > 0)
			close(cmd->fdin);
		if (cmd->fdout > 1)
			close(cmd->fdout);
	}
}

//frees a cmd_block, all its cmds, and all the leftover FDs
void	free_cmd_block(void)
{
	int		i;

	ft_free_null(g_meta->pid);
	if (g_meta->pipes)
	{
		i = -1;
		while (g_meta->pipes[++i])
		{
			if (g_meta->pipes[i][0] > 0)
				close(g_meta->pipes[i][0]);
			if (g_meta->pipes[i][1] > 0)
				close(g_meta->pipes[i][1]);
		}
		ft_free_null(g_meta->pipes);
	}
	if (g_meta->cmd_block)
	{
		i = -1;
		while (++i < g_meta->cmd_nb)
			free_cmd(g_meta->cmd_block[i]);
		ft_free_null(g_meta->cmd_block);
	}
}

/* Main logic loop of minishell. It initialises g_meta and signals and every cycle, it:
|- reads the inputed line
|- checks if said line empty
|- add it to the history
|- converts it into a cmd_block
|- checks if the global state is still valid
|- execute said cmd_block
|- frees the line buffer
0- repeats
Once the loop is over, it;
|- clears the history
|- frees all the leftover data */

void	minishell(void)
{
	init_meta();
	init_signals(1);
	while (g_meta->state >= MSTATE_NORMAL)
	{
		g_meta->state = MSTATE_NORMAL;
		g_meta->buf = readline("MNSH :) ");
		if (!g_meta->buf) //to make ctrl-D not segfault (if buffer == null)
			break ;
		if (!is_line_empty(g_meta->buf))
		{
			add_history(g_meta->buf);
			load_cmd_block(parse_line(g_meta->buf));
			if (g_meta->state == MSTATE_NORMAL)
			{
				execute_cmd_block();
				free_cmd_block();
			}
		}
		ft_free_null(g_meta->buf);
	}
	clear_history();
	ft_free_null(g_meta); //FREE ALL SUB PARTS before (free_all()?)
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)				//superfluous ?
		throw_error(ERR_AC);

	minishell();

	return (EXIT_FAILURE);
}

/*
void	minishell()
{
	if (!is_line_empty(g_meta->buf))
	{
		load_cmd_block(parse_line(g_meta->buf));
		if (g_meta->state == MSTATE_NORMAL)
			execute_cmd_block();
		free_cmd_block();
	}
}

int	main(int argc, char **argv)
{
	init_meta();
	init_signals(1);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		g_meta->buf = argv[2];
    	minishell();
		exit(g_meta->exit_status);
	}

	ft_free_null(g_meta); //FREE ALL SUB PARTS before (free_all()?)
	return (0);
}
*/
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
		while(g_meta->cmd_block[++i])
			print_cmd(g_meta->cmd_block[i]);
	}

	printf("\n");
}
*/