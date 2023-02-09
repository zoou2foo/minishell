/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2023/02/09 13:58:00 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take nothing. Return nothing. Use the global var to print ENV
void	get_env(void)
{
	int	i;

	i = 0;
	if (metadata->env)
	{
		while (metadata->env[i])
		{
			printf("%s\n", metadata->env[i]);
			i++;
		}
		exit (EXIT_SUCCESS);
	}
	exit (EXIT_FAILURE);
}