/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2022/12/18 07:34:56 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*buf;

	buf = readline("bash-Pew Pew> "); //readline will malloc it
	while (buf)
	{
		if (buf[0])
			add_history(buf);
		printf("%s\n", buf);
		free(buf); //but readline does not free it for us!
		buf = readline("bash-Pew Pew> ");
	}
	clear_history();
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {

// }

// COMMENT if ac is not 1, error; void argv.