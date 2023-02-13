/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/13 11:30:00 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the line read. Main purpose: READ
char	*gnl_minihell(void)
{
	char	buffer[10000];
	int		size;

	size = read(1, buffer, 10000);
	buffer[size] = '\0';
	return (ft_strdup(buffer));
}

// Return int of the fd[0] (to read); pipe first. Then, infinite loop to start
// reading what's in char *string (received) from the readline(prompt).
// then it has to be written in the pipe. And we return fd[0] so it can be read
int	execute_hd(char *string)
{
	int		pipe_hd[2];
	char	*gnl_return;
	char	*tmp;
	int		pid_hd;

	if (pipe(pipe_hd) == -1)
	{
		throw_error(ERR_PIPE);
		ft_free_null(string);
		exit (1);
	}
	printf("\nWaiting for heredoc input (<<%s) :\n", string);	//UI
	init_signals(1);
	//sig_ignore(); //My understanding: to make sure that SIGINT and SIGQUIT are ignored as we are about to fork and create another process. It has to block specific signals during exec too. Then, it ignores the previous signal returned (to change the behaviour of a process)
	gnl_return = NULL;
	pid_hd = fork();
	if (pid_hd == 0)
	{
		init_signals(3);
		//sig_heredoc(); //function to handle signals in the specific case of a here_doc.
		while (1)
		{
			write(1, "> ", 2);
			gnl_return = gnl_minihell();
			tmp = ft_strtrim(gnl_return, "\n");
			if ((ft_strncmp(tmp, string, ft_strlen(gnl_return))) == 0)
			{
				ft_free_null(tmp);
				printf("\n");										//UI
				break ;
			}
			write(pipe_hd[1], gnl_return, ft_strlen(gnl_return));
			ft_free_null(tmp);
			ft_free_null(gnl_return);
		}
		exit(0);
	}
	close(pipe_hd[1]); //il peut être fermé, car on n'écrit plus dedans
	waitpid(pid_hd, NULL, 0);
	ft_free_null(gnl_return);
	return (pipe_hd[0]);
}