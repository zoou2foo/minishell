/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/12 12:43:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*metadata;	//our global var

int	main(int ac, char **av, char **envp)
{

	(void)av;
	if (ac == 1)
	{
		metadata = ft_calloc(sizeof(t_meta), 1);
		t_cmd	*cmd = ft_calloc(sizeof(t_cmd), 1);
		cmd->cmd_args = ft_calloc(sizeof(char *), 3);
		cmd->cmd_args[0] = "cd";
		cmd->cmd_args[1] = "";
		init_struct(metadata, envp);
		metadata->buf = readline("bash-Pew Pew> ");
		while (metadata->buf)
		{
			if (metadata->buf[0])
				add_history(metadata->buf);
			change_dir(cmd);
			free(metadata->buf);
			metadata->buf = readline("bash-Pew Pew> ");
		}
		clear_history();
	}
	return (0);
}

void	init_struct(t_meta *meta, char **envp)
{
	meta->envp = envp;
	meta->copy_envp = envp;
}

// COMMENT if ac is not 1, error; void argv.
// COMMENT readline will malloc the char *buf, but it does NOT free it at the
// COMMENT end.

// int	main()
// {
// 	char	s[100];

// 	printf("%s\n", getcwd(s, 100));
// 	chdir("../Evaluation");
// 	printf("%s\n", getcwd(s, 100));
// 	return (0);
// }
