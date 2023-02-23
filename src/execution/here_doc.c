/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/23 15:20:25 by vjean            ###   ########.fr       */
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

//needed to pass hd in a child for signal.
//need to take the string, gnl_return and pipe_hd
void	child_in_hd(char *string, char *gnl_return, int *pipe_hd)
{
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		write(1, "> ", 2);
		gnl_return = gnl_minihell();
		tmp = ft_strtrim(gnl_return, "\n");
		if ((ft_strncmp(tmp, string, ft_strlen(gnl_return))) == 0)
		{
			ft_free_null(tmp);
			printf("\n");
			break ;
		}
		write(pipe_hd[1], gnl_return, ft_strlen(gnl_return));
		ft_free_null(tmp);
		ft_free_null(gnl_return);
	}
	close(pipe_hd[1]);
	close(pipe_hd[0]);
	close_all();
	free_cmd_block();
	exit(0);
}

//ft to shortent execute hd; dealing with pipe error
int	pipe_error(char *string)
{
	fatal_error(MSTATE_P_ERR);
	ft_free_null(string);
	return (-1);
}

//ft to shortent execute hd; dealing with fork error
int	error_fork(char *string)
{
	fatal_error(MSTATE_F_ERR);
	ft_free_null(string);
	return (-1);
}

// Return int of the fd[0] (to read); pipe first.
// And we return fd[0] so it can be read
int	execute_hd(char *string)
{
	int		pipe_hd[2];
	char	*gnl_return;
	int		pid_hd;

	if (pipe(pipe_hd) < 0)
		return (pipe_error(string));
	printf("\nWaiting for heredoc input (<<%s) :\n", string);
	init_signals(3);
	gnl_return = NULL;
	pid_hd = fork();
	if (pid_hd < 0)
		return (error_fork(string));
	if (pid_hd == 0)
		child_in_hd(string, gnl_return, pipe_hd);
	close(pipe_hd[1]);
	waitpid(pid_hd, NULL, 0);
	ft_free_null(gnl_return);
	init_signals(1);
	return (pipe_hd[0]);
}
