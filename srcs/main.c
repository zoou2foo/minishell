/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/11 16:38:07 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_meta	*meta;
	t_cmd	*cmd;

	(void)av;
	(void)envp;
	if (ac == 1)
	{
		meta = ft_calloc(sizeof(t_meta), 1);
		cmd = ft_calloc(sizeof(t_cmd), 1);
		init_struct(meta, envp);
		meta->buf = readline("bash-Pew Pew> ");
		while (meta->buf)
		{
			if (meta->buf[0])
				add_history(meta->buf);
			tokenizer_prompt(meta, cmd);
			printf("%s\n", cmd->meta_char);
			free(meta->buf);
			meta->buf = readline("bash-Pew Pew> ");
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