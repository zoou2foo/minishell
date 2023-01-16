/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/16 13:13:31 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>

extern	char	**environ;

typedef struct s_meta
{
	char	**env;
	char	*buf;		//variable pour garder ce qui est mis dans readline

}	t_meta;

extern	t_meta	*metadata;

								//else: use STDIN

	bool	has_output;		//if true: use output fd
	bool	has_outpipe;	//else if true: use pipe fd
								//else: use STDOUT

typedef struct s_cmd_block
{
	t_cmd_block	**cmds;
	bool		is_empty;
	bool		is_valid;

}			t_cmd_block;
// COMMENT: on initie toutes les variables a NULL puis on change par la suite

/* section one - all about our struct */
void	init_meta(void);

/* section two - built-ins */
void	do_exit(void);
//void	change_dir(t_cmd_block *cmd);
void	get_env(void);

/* section three - lexer and parser */

/* section four - */

/* section five - trying stuff */

#endif