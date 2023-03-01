/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:40:10 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//our global var
t_meta	*g_meta;

//sets things for a fatal error
void	fatal_error(int err_id)
{
	g_meta->state = err_id;
	g_meta->exit_status = EXIT_FAILURE;
	if (err_id == MSTATE_F_ERR)
		throw_error(ERR_FORK);
	else if (err_id == MSTATE_P_ERR)
		throw_error(ERR_PIPE);
	else
		throw_error(ERR_ERR);
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

//allocates memory for and fills the global g_meta var with default values
//(for env and path)
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

/* initialises g_meta and signals, and every cycle, it:
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
	while (g_meta->state >= MSTATE_NORMAL)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler_init_sig);
		g_meta->state = MSTATE_NORMAL;
		g_meta->must_fork = false;
		g_meta->buf = readline("MNSH :) ");
		if (!g_meta->buf)
			break ;
		if (!is_line_empty(g_meta->buf))
		{
			add_history(g_meta->buf);
			load_cmd_block(parse_line(g_meta->buf));
			if (g_meta->state == MSTATE_NORMAL)
				execute_cmd_block();
		}
		ft_free_null(g_meta->buf);
	}
	clear_history();
	free_all();
	ft_free_null(g_meta);
	exit (g_meta->exit_status);
}

//our main function. calls ministest if given "-c" in av[1]
int	main(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		throw_error(ERR_AC);
	minishell();
	return (EXIT_FAILURE);
}
