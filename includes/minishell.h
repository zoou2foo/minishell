/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 12:43:51 by llord            ###   ########.fr       */
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
extern	t_meta	*metadata;

typedef struct s_meta{
	char	**envp;
	char	**copy_envp;
	char	*buf;

}	t_meta;
// COMMENT: *buf: variable pour garder ce qui est mis dans readline

typedef struct s_cmd{
	char	**cmd_args;		//cmd name and following arguments
	char	*input;			//all the < redirection
	char	*output;		//all the >/>> redirection

}	t_cmd;
// COMMENT: **cmd_args; on initie strut à NULL; puis cela sera changé plus tard
// COMMENT: en fonction de ce qu'on obtient.
// COMMENT: *input ET *output; on initie struct à NULL aussi; mais plus tard, si
// COMMENT: à NULL, interpréter comme zéro.

/* section one - all about our struct */
void	init_struct(t_meta *meta, char **envp);

/* section built-ins */
void	do_exit(t_meta *meta);
void	change_dir(t_cmd *cmd);

/* section lexer and parser */

/* section four */

/* section five - trying stuff */

#endif