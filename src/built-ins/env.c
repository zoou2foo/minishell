/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 11:03:59 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Take nothing. Return nothing. Use the global var to print ENV
void	get_env(void)
{
	int	i;

	i = 0;
	while (metadata->env[i])
	{
		printf("%s\n", metadata->env[i]);
		i++;
	}
	exit (EXIT_SUCCESS);
}