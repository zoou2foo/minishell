/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:48 by vjean             #+#    #+#             */
/*   Updated: 2022/12/12 15:59:21 by vjean            ###   ########.fr       */
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