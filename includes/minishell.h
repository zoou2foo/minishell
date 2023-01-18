/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/18 15:23:39 by llord            ###   ########.fr       */
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


typedef struct s_cmd
{
	char	**cmd_args;	//cmd name and its following arguments
	int		argcount;		//number of function arguments (0 == no args, <0 == no cmd)
	bool	is_heredoc;		//call herdoc cmd and pipe out, ignore the rest

	char	*input;		//all the < redirection
	bool	has_input;		//if true: use input fd
	bool	has_inpipe;		//else if true: use pipe fd
	int		fdin;				//either pie of file fd
							//else: use STDIN

	char	*output;	//all the >/>> redirection
	bool	has_output;		//if true: use output fd
	bool	has_outpipe;	//else if true: use pipe fd
	int		fdout;				//either pie of file fd
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
	bool			is_after_space;	//this mf

}					t_token;

/* section one - all about our struct */
void	init_meta(void);

/* section two - built-ins */
void	do_exit(void);
void	change_dir(t_cmd *cmd);
void	get_env(void);

/* section three - lexer and parser */
t_token	*tokenize_input(char *line);


/* section four - */

/* section five - trying stuff */

#endif