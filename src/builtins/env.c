/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2023/02/21 15:08:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take nothing. Return nothing. Use the global var to print ENV
void	get_env(void)
{
	int	i;

	i = 0;
	free_cmd_block();
	if (g_meta->env)
	{
		while (g_meta->env[i])
		{
			printf("%s\n", g_meta->env[i]);
			i++;
		}
		exit (EXIT_SUCCESS);
	}
	exit (EXIT_FAILURE);
}
