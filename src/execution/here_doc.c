/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/03/01 09:10:06 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//reads a line from the terminal and returns it
char	*gnl_minihell(void)
{
	char	buffer[10000];
	int		size;

	size = read(1, buffer, 10000);
	buffer[size] = '\0';
	return (ft_strdup(buffer));
}

//execute the Heredoc in a child and exits when done
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

//fchecks for pipe errors
int	pipe_error(char *string)
{
	fatal_error(MSTATE_P_ERR);
	ft_free_null(string);
	return (-1);
}

//checks for fork errors
int	error_fork(char *string)
{
	fatal_error(MSTATE_F_ERR);
	ft_free_null(string);
	return (-1);
}

//execute a Heredoc in the terminal and returns a fd to its content
int	execute_hd(char *string)
{
	int		pipe_hd[2];
	char	*gnl_return;
	int		pid_hd;

	if (pipe(pipe_hd) < 0)
		return (pipe_error(string));
	printf("\nWaiting for heredoc input (<<%s) :\n", string);
	signal(SIGINT, &handler_hd_sig);
	signal(SIGQUIT, &handler_hd_sig);
	gnl_return = NULL;
	pid_hd = fork();
	if (pid_hd < 0)
		return (error_fork(string));
	if (pid_hd == 0)
		child_in_hd(string, gnl_return, pipe_hd);
	close(pipe_hd[1]);
	waitpid(pid_hd, NULL, 0);
	ft_free_null(gnl_return);
	return (pipe_hd[0]);
}
