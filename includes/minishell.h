/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/11 14:02:05 by vjean            ###   ########.fr       */
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

typedef struct s_meta{
	char	**envp;
	char	**copy_envp;
	char	*buf;

}	t_meta;

typedef struct s_cmd{
	char	**cmd_args;
	char	*input;
	char	*output;
	char	*meta_char;

}	t_cmd;

/* section one - all about our struct */
void	init_struct(t_meta *meta, char **envp);

/* section lexer and parser */
void	tokenizer_prompt(t_meta *meta, t_cmd *cmd);

/* section built-ins */

/* section four */

/* section five - trying stuff */


#endif