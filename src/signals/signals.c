/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/04 10:20:14 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handler_parent_sig(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 		sigignore(SIGQUIT);
// 	}
// }

void	handler_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		sigignore(SIGINT);
	}
	if (sig == SIGQUIT)
	{
		sigignore(SIGQUIT);
	}
}

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
		rl_redisplay();
		sigignore(SIGQUIT);
	}
}

//Initialize the signals for the minishell.
// Received an int as a flag to know where it is in the process; parent or child
// Define the signals struct to know which signal was received.
// Depending on the flag, each process has it's handler for signals.
void	init_signals(int flag)		//call me in child too
{
	struct sigaction	sa;
	sa.sa_mask = SIGINFO; //pour savoir quel signal tu as reçu
	sa.sa_flags = SA_RESTART; //flag pour etre sur qu'il ne soit pas undefine state when interrupted
	if (flag == 1)
		sa.sa_handler = &handler_sig;
	// else if (flag == 2)
	// 	sa.sa_handler = &handler_parent_sig; //superflu
	else if (flag == 3)
		sa.sa_handler = &handler_child_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
