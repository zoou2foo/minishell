/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:25:49 by vjean             #+#    #+#             */
/*   Updated: 2023/01/17 11:24:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(2, "getcwd error", 12);
		exit (1);
	}
	else
		printf("%s\n", cwd);
}

// COMMENT It works! TESTED. **Still have a question: not sure if we really need
// COMMENT the error message. Might be manage by export?? Need to talk to Cole

/*
It was tested with this:
if (ft_strncmp(metadata->buf, "pwd", 3) == 0)
				get_pwd();

*/