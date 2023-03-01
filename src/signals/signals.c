/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:22:48 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//initializes the signals for minishell
void	handler_init_sig(int sig)
{
	(void)sig;
	g_meta->exit_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//prints a newline when a signal is spotted
void	handler_child_sig(int sig)
{
	(void)sig;
	printf("\n");
}

//signal handler for child (including hd)
void	handler_hd_sig(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
}

//signal handler for parent
void	handler_parent_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_meta->exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		sigignore(SIGQUIT);
	}
}
