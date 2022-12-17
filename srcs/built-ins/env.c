/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:10:01 by vjean             #+#    #+#             */
/*   Updated: 2022/12/17 15:18:41 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->copy_envp[i])
	{
		printf("%s\n", data->copy_envp[i]);
		i++;
	}
}

// COMMENT need to create a copy of env. It's the copy that we will use
// COMMENT throughout the program as it will be modified. You don't want 
// COMMENT your env to be modified when you quit.