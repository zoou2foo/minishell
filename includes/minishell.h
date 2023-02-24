/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/02/24 15:35:40 by llord            ###   ########.fr       */
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

extern char	**environ;

enum e_ttype
{
	TTYPE_ERROR		= -1,
	TTYPE_EMPTY		= 0,
	TTYPE_NORMAL	= 1,
	TTYPE_S_QUOTE	= 2,
	TTYPE_D_QUOTE	= 3,
	TTYPE_EXPAND	= 4,
	TTYPE_REDIR_IN	= 5,
	TTYPE_HEREDOC	= 6,
	TTYPE_S_RDR_OUT	= 7,
	TTYPE_D_RDR_OUT	= 8,
	TTYPE_PIPE		= 9
};

enum e_mstate
{
	MSTATE_F_ERR	= -3,
	MSTATE_P_ERR	= -2,
	MSTATE_ERROR	= -1,
	MSTATE_NORMAL	= 0,
	MSTATE_O_BRACK	= 1,
	MSTATE_O_PIPE	= 2,
	MSTATE_O_REDIR	= 3,
	MSTATE_BAD_FD	= 4
};

/*	ERROR MESSAGE	*/
# define ERR_ERR	"Process Error : Error code not found\n"
# define ERR_PIPE	"Process Error : Couldn't pipe() properly\n"
# define ERR_FORK	"Process Error : Couldn't fork() properly\n"
# define ERR_PWD	"Process Error : Couldn't getcwd() properly\n"
# define ERR_PATH	"Process Error : PATH variable not found\n"
# define ERR_ENV	"Process Error : Environment does not exist\n"
# define ERR_EXIT	"Process Warning : Child did not exit properly\n"

# define ERR_ARG	"Input Error : No argument given\n"
# define ERR_ARG2	"Input Error : Invalid argument given\n"
# define ERR_ARG3	"Input Error : Too many arguments given\n"
# define ERR_CD		"Input Error : Invalid path given\n"
# define ERR_CMD	"Input Error : Invalid command given\n"
# define ERR_FILE	"Input Error : Invalid filename given\n"
# define ERR_VAR	"Input Error : Invalid variable given\n"
# define ERR_QUOTE	"Input Error : Invalid quotation (unclosed)\n"
# define ERR_TOKEN	"Input Error : Invalid token combination\n"
# define ERR_AC		"Input Warning : Minishell does not accept arguments\n"

typedef struct s_token
{
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
	bool			is_joined;
}					t_token;

typedef struct s_cmd
{
	char	**cmd_args;
	int		argcount;
	int		id;
	int		fdin;
	int		fdout;
	bool	is_built_in;
}			t_cmd;

typedef struct s_meta
{
	char	**env;
	char	**paths;
	char	*buf;
	t_cmd	**cmd_block;
	int		cmd_nb;
	int		**pipes;
	int		*pid;
	int		exit_status;
	int		state;

}	t_meta;

extern t_meta	*g_meta;

// ===== FROM FREEER =====
void	free_cmd(t_cmd *cmd);
void	free_cmd_block(void);
void	free_all(void);

// ===== FROM MAIN =====
void	fatal_error(int err_id);
int		is_line_empty(char *line);
void	init_meta(void);

// ===== FROM BUILT-INS =====
void	change_dir(t_cmd *cmd);
void	do_echo(t_cmd *cmd);
void	get_env(void);
void	do_exit(t_cmd *cmd);
void	close_pipes(void);
void	do_export(t_cmd *cmd);
int		find_var(char *str);
bool	is_valid_name(char *str);
void	get_pwd(void);
void	do_unset(t_cmd *cmd);

// ===== FROM EXECUTOR =====

//from builtins_cmds
bool	is_built_in(char *cmd_arg);
void	execute_builtins(t_cmd *cmd);
bool	built_ins_childable(t_cmd *cmd);

//from execution_utils
void	close_fds(t_cmd *cmd);
void	close_all(void);
void	throw_error(char *str);
bool	is_same(char *arg, char *str);

//from execution
void	child_process(t_cmd *cmd);
void	execute_cmd_block(void);

//from here_doc
int		execute_hd(char *string);

//from path_cmds
void	fill_path_tab(void);
void	exec_with_paths(t_cmd *cmd);

// ===== FROM PARSING =====

//from expander
char	*expand(char *str1);
char	*expand_quote(char *str1);

//from converter_utils
void	check_merge_error(t_token *node);
void	get_redirs_in(t_token *node, t_cmd *cmd);
void	get_redirs_out(t_token *node, t_cmd *cmd);
bool	has_fd_error(t_cmd *cmd);

//from converter
void	load_cmd_block(t_token **head);

//from parser
t_token	**parse_line(char *line);

//from token_finder
int		find_length(t_token *head);
t_token	*find_head(t_token *tail);
t_token	*find_tail(t_token *head);

//from token_maker
t_token	*new_token(char *str, int len, int type);
t_token	*merge_tokens(t_token *prev, t_token *next);
t_token	*insert_token(t_token *node, t_token *prev, t_token *next);
t_token	*replace_token(t_token *new, t_token *old);
void	add_token(t_token *token, t_token **head);

//from token_remover
void	free_token(t_token *node);
void	free_token_list(t_token *head);
void	destroy_token(t_token *node);
t_token	*cut_token(t_token *node);
t_token	*empty_token(t_token *node);

//from tokenizer_utils
bool	is_in_expansion(char c);
int		find_redir_out(char *line, int i, t_token **head);
int		find_redir_in(char *line, int i, t_token **head);
int		find_quote(char *line, int i, t_token **head, char c);
int		find_leftover(char *line, int i, t_token **head);

//from tokenizer
void	create_token_list(char *line, t_token **head);
void	expand_token_list(t_token *head);
t_token	*remove_empty_list(t_token *head);
t_token	*merge_token_list(t_token *head);

// ===== FROM SIGNALS =====
void	init_signals(int flag);

#endif