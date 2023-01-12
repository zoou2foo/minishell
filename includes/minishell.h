/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2023/01/10 15:01:08 by llord            ###   ########.fr       */
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
	char	*buf; //variable pour garder ce qui est mis dans readline

}	t_meta;

typedef struct s_cmd{
	char	**cmd_args; //init struct on met à NULL; puis ça sera rempli en fonction de ce que ça obtient
	char	*input; // init struct on met à NULL; mais plus tard si à NULL, interpréter à zéro.
	char	*output;

}

/* section one - all about our struct */
void	init_struct(t_data *data, char **envp);

/* section two */

/* section three */

/* section four */

/* section five - trying stuff */
void	try_something(t_data *data);

#endif