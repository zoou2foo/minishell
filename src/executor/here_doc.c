/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/02/03 11:19:46 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1. Checker dans l'ensemble de la ligne de commande reçu si on a un
here_doc. Même si plus loin, il faut qu'il soit exécuté en premier.
2. Checker si on a bien un délimiteur; car besoin d'y faire référence durant gnl
3. 

*/

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

	if (pipe(pipe_hd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		ft_free_null(string);
		exit (1);
	}
	while (1)
	{
		gnl_return = gnl_minihell();
		tmp = ft_strtrim(gnl_return, "\n");
		if ((ft_strncmp(tmp, string, ft_strlen(gnl_return))) == 0)
		{
			free(tmp);
			break ;
		}
		write(pipe_hd[1], gnl_return, ft_strlen(gnl_return));
		free(tmp);
		free (gnl_return);
	}
	//dup2(*metadata->pipe_hd[0], STDIN_FILENO); parce que la redirection doit se passer dans le child
	//close(*metadata->pipe_hd[0]); // doit rester ouvert, sinon, je le perds.
	close(pipe_hd[1]); //il peut être fermé, car on n'écrit plus dedans
	free (gnl_return);
	return (pipe_hd[0]);
}