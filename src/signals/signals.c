/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/15 13:20:54 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when in parent; a ft signals have to do
// SIGINT for ctrl-C
// SIGQUIT for ctrl-backslash
void	handler_parent_sig(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3");
}

//at the very end of execute_cmd_block; out of all the loops
//main handler
void	handler_sig(int sig)
{
	if (sig == SIGINT)
	{
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
// Received an int as a flag to know where it is in the process; parent or child
// Define the signals struct to know which signal was received.
// Depending on the flag, each process has it's handler for signals.
//SIGINFO: to know which signal received
// SA_RESTART: flag to make sure that it does not in an undefine state when
//interrupted
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
