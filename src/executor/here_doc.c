/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:11:37 by vjean             #+#    #+#             */
/*   Updated: 2023/01/30 11:44:54 by vjean            ###   ########.fr       */
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

int	execute_hd(t_cmd *cmd) //à modifier.
{
	char	*gnl_return;
	char	*tmp;

	if (pipe(metadata->pipes) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		free(cmd); //called ft_free_null
		exit (1);
	}
	while (1)
	{
		gnl_return = gnl_minihell();
		tmp = ft_strtrim(gnl_return, "\n");
		if ((ft_strncmp(tmp, cmd->cmd_args[1], ft_strlen(gnl_return))) == 0) //maybe will need to change parameter2
		{
			free(tmp);
			break ;
		}
		write(cmd->pipe_hd[1], gnl_return, ft_strlen(gnl_return));
		free(tmp);
		free (gnl_return);
	}
	dup2(cmd->pipe_hd[0], STDIN_FILENO); //Je veux return(pipe_hd[0])
	close(cmd->pipe_hd[0]); //pas sûr que je dois le fermer si c'est ça que je renvoie
	close(cmd->pipe_hd[1]);
	free (gnl_return);
	return (cmd->pipe_hd[0]);
}