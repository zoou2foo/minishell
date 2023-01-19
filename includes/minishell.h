/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:13:50 by vjean             #+#    #+#             */
/*   Updated: 2023/01/19 13:20:39 by vjean            ###   ########.fr       */
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

extern	char	**environ; //on peut la mettre dans notre main et ainsi pas avoir de globale

typedef struct s_meta
{
	char	**env; //elle pourrait devenir notre globale
	char	*buf;		//variable pour garder ce qui est mis dans readline

}	t_meta;

extern t_meta	*metadata;


typedef struct s_cmd
{

	char	**cmd_args;	//cmd name and its following arguments
	int		argcount;		//number of function arguments (0 == no args, <0 == no cmd)
	bool	is_heredoc;		//call herdoc cmd and pipe out, ignore the rest

	char	*input;		//all the < redirection
	bool	has_input;		//if true: use input fd
	bool	has_inpipe;		//else if true: use pipe fd
	char	*output;	//all the >/>> redirection
	bool	has_output;		//if true: use output fd
	bool	has_outpipe;	//else if true: use pipe fd
							//else: use STDOUT
}			t_cmd;

typedef struct s_cmd_node
{
	t_cmd				*cmd;
	struct s__cmd_node	*next_node;
	struct s__cmd_node	*previous_node;	//superfluous(?)
	bool				is_empty;
	bool				is_valid;
}						t_cmd_node;

typedef struct s_cmd_block
{
	t_cmd_node	*head_node;
	t_cmd_node	*tail_node;		//superfluous(?)
	t_cmd		**cmds;			//superfluous(?)
	int			cmd_count;
	bool		is_empty;
	bool		is_valid;

}			t_cmd_block;

typedef struct s_token
{
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
	bool			is_joined;	//wheter it touches the previous token (no spaces)

}					t_token;

/* section one - all about our struct */
void	init_meta(void);

/* section two - built-ins */
void	do_exit(t_cmd *cmd); //Need to change back to void.
void	change_dir(t_cmd *cmd);
void	get_env(void);
void	get_pwd(void);
void	do_unset(t_cmd *cmd);
int		check_arg_4_unset(t_cmd *cmd);

/* section three - lexer and parser */
t_token	*tokenize_input(char *line);
char	*do_expansion(char *str);

/* section four - */

/* section five - trying stuff */


#endif