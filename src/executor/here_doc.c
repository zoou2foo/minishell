/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/01/30 16:44:08 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1. Checker dans l'ensemble de la ligne de commande reçu si on a un
here_doc. Même si plus loin, il faut qu'il soit exécuté en premier.
2. Checker si on a bien un délimiteur; car besoin d'y faire référence durant gnl
3.

*/

char	*gnl_minihell(void)
{
	char	buffer[10000];
	int		size;

	size = read(1, buffer, 10000);
	buffer[size] = '\0';
	return (ft_strdup(buffer));
}

int	execute_hd(char *string)
{
	char	*gnl_return;
	char	*tmp;

	if (pipe(*metadata->pipe_hd) == -1)
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
		write(*metadata->pipe_hd[1], gnl_return, ft_strlen(gnl_return));
		free(tmp);
		free (gnl_return);
	}
	dup2(*metadata->pipe_hd[0], STDIN_FILENO); //Je veux return(pipe_hd[0])
	close(*metadata->pipe_hd[0]); //pas sûr que je dois le fermer si c'est ça que je renvoie
	close(*metadata->pipe_hd[1]);
	free (gnl_return);
	return (*metadata->pipe_hd[0]);
}