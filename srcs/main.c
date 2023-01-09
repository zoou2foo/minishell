/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2023/01/09 12:49:45 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	// char	*buf;
// 	t_data	*data;

// 	(void)av;
// 	if (ac == 1)
// 	{
// 		data = ft_calloc(sizeof(t_data), 1);
// 		init_struct(data, envp);
// 		data->buf = readline("bash-Pew Pew> ");
// 		while (data->buf)
// 		{
// 			if (data->buf[0])
// 				add_history(data->buf);
// 			try_something(data);
// 			free(data->buf);
// 			data->buf = readline("bash-Pew Pew> ");
// 		}
// 		clear_history();
// 	}
// 	return (0);
// }

// void	init_struct(t_data *data, char **envp)
// {
// 	data->envp = envp;
// 	data->copy_envp = envp;
// }

// void	try_something(t_data *data)
// {
// 	printf("trying some stuff\n");
// 	printf("%s\n", data->buf);
// 	printf("and??");
// }

// int	main()
// {
// 	char	s[100];

// 	printf("%s\n", getcwd(s, 100));
// 	chdir("../Evaluation");
// 	printf("%s\n", getcwd(s, 100));
// 	return (0);
// }

int	main()
{
	
}

// COMMENT if ac is not 1, error; void argv.
// COMMENT readline will malloc the char *buf, but it does NOT free it at the
// COMMENT end.