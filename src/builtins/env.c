/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2023/02/28 10:57:15 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//prints ENV from g_meta->env
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
