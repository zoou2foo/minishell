/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 14:54:40 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_parent_sig(int sig) //when in parent
{
	if (sig == SIGINT)	//Ctrl-C
	{
		printf("\n");
	}
	if (sig == SIGQUIT)	//Ctrl-backslash
	{
		printf("Quit: 3");
	}
}

void	handler_child_sig(int sig) //when in child
{
	if (sig == SIGINT)	//Ctrl-C
	{
		signal(SIGINT, SIG_DFL);
		//sigignore(SIGINT);
	}
	if (sig == SIGQUIT)	//Ctrl-backslash
	{
		sigignore(SIGQUIT);
	}
}

void	handler_sig(int sig) //at the very end of execute_cmd_block; out of all the loops
{
	if (sig == SIGINT)	//Ctrl-C
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	if (sig == SIGQUIT)	//Ctrl-backslash
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
void	init_signals(int flag)		//in child, I end up doing: signal(SIGINT, SIG_DFL); now maybe handler_child_sig is superfluous
{
	struct sigaction	sa;

	sa.sa_mask = SIGINFO; //pour savoir quel signal tu as reçu
	sa.sa_flags = SA_RESTART; //flag pour etre sur qu'il ne soit pas undefine state when interrupted
	if (flag == 1)
		sa.sa_handler = &handler_sig;
	else if (flag == 2)
		sa.sa_handler = &handler_parent_sig;
	else if (flag == 3)
		sa.sa_handler = &handler_child_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
