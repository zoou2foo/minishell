/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/25 16:01:16 by vjean            ###   ########.fr       */
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

enum e_ttype
{
	TTYPE_ERROR		= -1,
	TTYPE_EMPTY		= 0,
	TTYPE_NORMAL	= 1,	// _	(cmds/args)
	TTYPE_S_QUOTE	= 2,	//'_'	(string without expansion)
	TTYPE_D_QUOTE	= 3,	//"_"	(string with expansion)
	TTYPE_EXPAND	= 4,	//$_	(expansion)
	TTYPE_REDIR_IN	= 5,	// <	(input path)
	TTYPE_HEREDOC	= 6,	//<<	(heredoc EOF word)
	TTYPE_S_RDR_OUT	= 7,	// >	(output path (replace))
	TTYPE_D_RDR_OUT	= 8,	//>>	(output path (append))
	TTYPE_PIPE		= 9		// |	(pipe)
};

typedef struct s_meta
{
	char	**env; //elle pourrait devenir notre globale
	char	*buf;		//variable pour garder ce qui est mis dans readline
	char	**path; //contient la ligne PATH pour être en mesure de trouver les system cmds
	int		exit_status;

}	t_meta;

extern t_meta	*metadata;

typedef struct s_token
{
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
	bool			is_joined;	//whether it touches the previous token (no spaces)

}					t_token;

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

typedef struct s_cmd_block
{
	t_token		**token_array;
	t_cmd		**cmds;
	int			cmd_count;
	bool		is_empty;
	bool		is_valid;

}			t_cmd_block;

/* 		MAIN			*/
void	init_meta(void);
void	print_token_list(t_token *head);

/* 		BUILT-INS		*/
void	do_exit(t_cmd *cmd); //Need to change back to void.
void	change_dir(t_cmd *cmd);
void	get_env(void);
void	get_pwd(void);
void	do_unset(t_cmd *cmd);
int		check_arg_4_unset(t_cmd *cmd);
void	do_export(t_cmd *cmd);
int		check_arg_4_export(t_cmd *cmd);
char	**sort_env(void);
void	do_echo(t_cmd *cmd);
int		array_len(void);
int		check_double(char **new_env, char *tmp);
void	array_sorted(char **new_env, char *tmp, int size);

/*		 EXPANDER		*/
char	*expand(char *str1);
char	*expand_quote(char *str1);

//from parser
t_token	**parse_line(char *line);

//from tokenizer
bool	is_space(char c);	//à mettre dans libft
bool	is_capital(char c);	//à mettre dans libft (USE ANOTHER FUNCTION)
t_token	*create_token_list(char *line);
void	expand_token_list(t_token *head);
t_token	*merge_token_list(t_token *head);

//from token_handler
void	free_token(t_token *node);
t_token	*new_token(char *str, int len, int type);
void	add_token(t_token *token, t_token **head);
t_token	*find_head(t_token *tail);
t_token	*find_tail(t_token *head);
t_token	*merge_tokens(t_token *prev, t_token *next);
t_token	*insert_token(t_token *node, t_token *prev, t_token *next);
t_token	*replace_token(t_token *new, t_token *old);
void	cut_token(t_token *node);
void	destroy_token(t_token *node);

/*		SYSTEM_CMDS		*/
void	fill_path_tab(void);
void	error_fill_path(void);
char	*find_cmd(t_cmd *cmd);

/* section five - trying stuff */
void	print_tab_env(void);

#endif