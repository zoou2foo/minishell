/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:27:34 by vjean             #+#    #+#             */
/*   Updated: 2022/12/21 15:32:34 by vjean            ###   ########.fr       */
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

typedef struct s_data{
	char	**envp;
	char	**copy_envp;
	char	*buf; //variable pour garder ce qui est mis dans readline

}	t_data;

/* section one - all about our struct */
void	init_struct(t_data *data, char **envp);

/* section two */

/* section three */

/* section four */

/* section five - trying stuff */
void	try_something(t_data *data);

#endif