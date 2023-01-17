/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2023/01/17 08:18:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(void)
{
	int	i;

	i = 0;
	while (metadata->env[i])
	{
		printf("%s\n", metadata->env[i]);
		i++;
	}
}

// COMMENT It works! TESTED.

/* What I used to test it in the main:
if (ft_strncmp(metadata->buf, "env", 3) == 0)
				get_env();
*/