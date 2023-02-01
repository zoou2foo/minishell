/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:30:47 by vjean             #+#    #+#             */
/*   Updated: 2023/02/01 11:42:19 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_n_fork(int	index)
{
	metadata->pipes[index] = ft_calloc(index, sizeof(int));
	printf("madafakas\n");
	if (pipe(metadata->pipes == -1)) //TOFIX segfault here
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		ft_free_null(metadata);
		exit (1);
	}
	write(2, "bob\n", 4);
	metadata->pid = fork();
	if (metadata->pid == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		ft_free_null(metadata);
		exit (1);
	}
}

void	child_process(t_cmd *cmd)
{
	metadata->cmd_path = find_cmd(cmd); // peut-être prob ici, car dans la ft, je regarde cmd_args[0], je crois qu'il faut envoyer l'index de la boucle while de minishell pour savoir à quelle cmd on est rendu.
	write(2, "ready for execution", 19);
	//execute_child(); //--> now, real execution. Create a file for it.
}

void	minishell(t_cmd *cmd)
{
	t_token	**head;
	int		index;
	int		flag;

	head = parse_line(metadata->buf);
	load_cmd_block(head, cmd);
	fill_path_tab();
	index = 0;
	//flag = check_cmd_or_builtins(cmd); //to be called again in child process to kill it after if builtins
	metadata->pipes = ft_calloc(metadata->cmd_nb, sizeof(int));
	while (index < metadata->cmd_nb) //ajouter moins 1 ou non...
	{
		printf("pew pew\n");
		pipe_n_fork(index);
		if (metadata->pid > 0)
		{
			dup2(*metadata->pipes[cmd->id - 1], STDIN_FILENO); //dup2(pipes[id - 1][1], STDIN)
			printf("prêt pour parent_process");
			// close(fdout[0]);
			// close(fdout[1]);
		}
		else if (metadata->pid == 0)
			write(2, "child\n", 6);
			child_process(cmd);
		index++;
	}
	waitpid(metadata->pid, NULL, 0);
}





