/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 09:22:20 by vjean            ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>

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

enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_NORMAL	= 0,
	MSTATE_O_BRACK	= 1,
	MSTATE_CLOSING	= 2
};

/*	ERROR MESSAGE	*/
# define ERR_PWD	"Process Error : Couldn't getcwd() properly\n"
# define ERR_PID	"Process Error : Couldn't fork() properly\n"
# define ERR_PIPE	"Pipe Error : Invalid file descriptor\n"
# define ERR_QUOTE	"Input Error : Non terminated quotes\n"
# define ERR_CD		"Input Error : Invalid path given\n"
# define ERR_CMD	"Input Error : Command not found\n"
# define ERR_ARG	"Input Error : No argument given\n"

# define ERR_AC		"Input Warning : Minishell executable does not take arguments\n"
# define ERR_PATH	"Path Warning : Path variable not in environment\n"
# define ERR_ENV	"Environment Warning : Variable not found\n"
# define ERR_DIR	"Directory Warning : Directory not found\n"

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
	int		id;				//id of this cmd (in relation to others in this cycle)
	char	*input;		//the last < redirection
	int		fdin;			//the fd for the piping
	char	*output;	//the last >/>> redirection
	int		fdout;			//the fd for the piping
	bool	append_output;	//if the output needs extend the file or overwrite it
	bool	is_built_in;	//whether the command is a built in
	bool	has_cmd;					//implement me!!!
}			t_cmd;

typedef struct s_meta
{
	char	**env;		//elle pourrait devenir notre globale
	char	**paths;    //contient la ligne PATH pour être en mesure de trouver les system cmds
	char	*buf;			//variable pour garder ce qui est mis dans readline
	t_cmd	**cmd_block;	//all commands to be called this cycle
	int		cmd_nb;			//nb of commands to be called this cycle
	int		**pipes;	//all the pipes fd for the current command line
	int		*pid;
	int		exit_status;
	int		state;			//what to do on next cmd and/or cycle

}	t_meta;

extern t_meta	*metadata;

/* 		MAIN			*/
void	init_meta(void);
void	print_cmd(t_cmd *cmd);
void	print_token_list(t_token *head, bool start_with_newline);

/* 		BUILT-INS		*/
void	do_exit(t_cmd *cmd); //Need to change back to void.
void	change_dir(t_cmd *cmd);
void	get_env(void);
void	get_pwd(void);
void	do_unset(t_cmd *cmd);
int		check_arg_4_unset(t_cmd *cmd);
void	do_export(t_cmd *cmd);
void	do_echo(t_cmd *cmd);
int		env_length(void);
void	reassign_var(int j, t_cmd *cmd);
void	refill_path_tab(char *str);

//from expander
char	*expand(char *str1);
char	*expand_quote(char *str1);

//from parser
t_token	**parse_line(char *line);

//from converter
void	load_cmd_block(t_token **head);

//from tokenizer
bool	is_space(char c);					//à mettre dans libft
bool	is_in_expansion(char c);
t_token	*create_token_list(char *line);
void	expand_token_list(t_token *head);
t_token	*merge_token_list(t_token *head);
t_token	*remove_empty_list(t_token *head);

//from token_handler
void	free_token(t_token *node);
t_token	*new_token(char *str, int len, int type);
void	add_token(t_token *token, t_token **head);
int		find_length(t_token *head);
t_token	*find_head(t_token *tail);
t_token	*find_tail(t_token *head);
t_token	*merge_tokens(t_token *prev, t_token *next);
t_token	*insert_token(t_token *node, t_token *prev, t_token *next);
t_token	*replace_token(t_token *new, t_token *old);
t_token	*cut_token(t_token *node);
t_token	*empty_token(t_token *node);
void	destroy_token(t_token *node);

/*		SYSTEM_CMDS		*/
void	fill_path_tab(void);
void	throw_error(char *str);
void	exec_with_paths(t_cmd *cmd);

/*		HERE_DOCUMENT	*/
int		execute_hd(char *string);
void	sig_heredoc(void);
void	hd_handler(int signum);
void	sig_ignore(void);

/*		SIGNALS			*/
void	init_signals(int flag);

/*		PRE_EXECUTION	*/
void	execute_cmd_block(void);
void	waitchild();

/*		UTILS_TO_EXEC	*/
int		is_built_in(char *cmd_arg);
void	execute_builtins(t_cmd *cmd);
int		built_ins_childable(t_cmd *cmd);

/* section five - trying stuff */
void	print_tab_env(void); //à enlever

#endif