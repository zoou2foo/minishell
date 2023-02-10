
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:50:00 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 14:24:00 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_parent_sig(int sig)
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

void	handler_child_sig(int sig)
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

void	handler_sig(int sig)
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

//besoin de me faire expliquer la partie ci-dessous ⬇️ (VJ)
void	sig_ignore(void) //je peux adapter à partir de notre init_sign
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = SIG_IGN;
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigint.sa_mask);
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigint.sa_flags = 0;
	sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	sig_heredoc(void) //initie les signaux pour here_doc
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = hd_handler; //fonction qui dit quoi faire avec les signaux dans hd
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigint.sa_mask);
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigint.sa_flags = 0;
	sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	hd_handler(int signum)
{
	struct termios	termios_copy;
	struct termios	termios_repl;

	tcgetattr(0, &termios_copy);
	termios_repl = termios_copy;
	termios_repl.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_repl);
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(0);
	}
}
// partie à revoir ⬆️


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
	else if (flag == 2)
		sa.sa_handler = &handler_parent_sig; //superflu
	else if (flag == 3)
		sa.sa_handler = &handler_child_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
