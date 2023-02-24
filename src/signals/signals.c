/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/24 10:47:40 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when in parent; tells what to do with signals
void	handler_parent_sig(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3");
}

//main handler; to tells what to do with signals
void	handler_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_meta->exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		sigignore(SIGQUIT);
	}
}

//signals handler in hd
void	handler_hd_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		sigignore(SIGQUIT);
	}
}

//Initialize the signals for the minishell.
//flag send the right hangler depending on the value of flag
void	init_signals(int flag)
{
	struct sigaction	sa;

	sa.sa_mask = SIGINFO;
	sa.sa_flags = SA_RESTART;
	if (flag == 1)
		sa.sa_handler = &handler_sig;
	else if (flag == 2)
		sa.sa_handler = &handler_parent_sig;
	else if (flag == 3)
		sa.sa_handler = &handler_hd_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
