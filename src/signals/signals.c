/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 09:32:01 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//call before readline
void	handler_init_sig(int sig)
{
	(void)sig;
	// if (sig == SIGINT)
	// {
		g_meta->exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	// }
	// if (sig == SIGQUIT)
	// {
	// 	rl_on_new_line(); //besoin ou non?
	// 	sigignore(SIGQUIT);
	// }
}

void	handler_child_sig(int sig)
{
	(void)sig;

	printf("allo\n");
	rl_on_new_line();
	rl_replace_line("", 0);

}

//signals handler in child (including hd)
void	handler_hd_sig(int sig)
{
	(void)sig;
	// if (sig == SIGINT)
	// {
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
	// }
	// if (sig == SIGQUIT)
	// {
	// 	rl_on_new_line();
	// 	sigignore(SIGQUIT);
	// }
}

//main handler; to tells what to do with signals
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
		//rl_on_new_line();
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
	if (flag == E_SIG_START)
		sa.sa_handler = &handler_init_sig;
	else if (flag == E_SIG_PRNT)
		sa.sa_handler = &handler_parent_sig;
	else if (flag == E_SIG_CHLD)
		sa.sa_handler = &handler_child_sig;
	else if (flag == E_SIG_HD)
		sa.sa_handler = &handler_hd_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
