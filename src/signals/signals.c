
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

//besoin de me faire expliquer la partie ci-dessous ⬇️ (VJ)
void	sig_ignore(void)
{
 	struct sigaction	sa_sigint;
 	struct sigaction	sa_sigquit;

 	sa_sigint.sa_handler = SIG_IGN; //sets SIGINT to SIG_IGN (ignore)
 	sa_sigquit.sa_handler = SIG_IGN; //sets SIGQUIt to SIG_IGN (ignore)
 	sigemptyset(&sa_sigint.sa_mask); //init signal mask to empty set. Signal mask specifies which signals should be blocked during exec.
 	sigemptyset(&sa_sigquit.sa_mask); //same as previous but for sigquit
 	sa_sigint.sa_flags = 0; //to be called with default behaviour
 	sa_sigquit.sa_flags = 0; //to be called with default behaviour
 	sigaction(SIGINT, &sa_sigint, NULL); //to install signal handler for sigint. NULL: no info about previous signal returned
 	sigaction(SIGQUIT, &sa_sigquit, NULL); //same as previous but on sigquit
}

void	sig_heredoc(void) //initie les signaux pour here_doc
{
 	struct sigaction	sa_sigint;
 	struct sigaction	sa_sigquit;

 	sa_sigint.sa_handler = hd_handler; //it sets SIGINT to hd_handler function. So, SIGINT will execute what it's in hd_handler
 	sa_sigquit.sa_handler = SIG_IGN; //it sets the signal handler for the SIGQUIT to SIG_IGN. It's to make sure that SIGQUIT does not terminate the entire minishell(as I understand it)
 	sigemptyset(&sa_sigint.sa_mask); //init signal mask to the empty set. Signal mask specifies which signals should be blocked during exec.
 	sigemptyset(&sa_sigquit.sa_mask); //same as previous but with sigquit
 	sa_sigint.sa_flags = 0; //to be called with default behaviour
 	sa_sigquit.sa_flags = 0; //to be called with default behaviour
 	sigaction(SIGINT, &sa_sigint, NULL); //to install signal handler for sigint. NULL: no info about previous signal returned
 	sigaction(SIGQUIT, &sa_sigquit, NULL); //same as previous but on sigquit
}

void	hd_handler(int signum) //function to handle signals in here_doc case
{
	struct termios	termios_copy; //where we copy the terminal attr
	struct termios	termios_repl; //repl for replacement

	tcgetattr(0, &termios_copy); //retrieves the terminal attr. for fd 0. It is stored in termios_copy struct
	termios_repl = termios_copy; //then make a copy in termios_repl
	termios_repl.c_lflag &= ~ECHOCTL; //modifies the c_lflag of termios_repl. c_lflag is a bit mask that specifies various local options for the terminal. ECHOCTL determines whether control character, such as ctrl-C, are echoed or not. Using bitwise-AND operator '&' and the bitwise-NOT operator '~', it turns off ECHOCTL in c_lflag field.
	tcsetattr(0, 0, &termios_repl); //it sets the terminal attr. for fd 0(terminal) to the modified termios_struct repl. Cannot just use termios_copy as we did not modify the c_lflag and ECHOCTL.
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
