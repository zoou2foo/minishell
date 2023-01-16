/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:46:03 by vjean             #+#    #+#             */
/*   Updated: 2023/01/16 13:00:23 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer_prompt(t_meta *meta, t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("pew pew\n");
	printf("%s\n", meta->buf);
	while (meta->buf[i] != '\0')
	{
		if (meta->buf[i] == 124 || meta->buf[i] == 38 || meta->buf[i] == 59
			|| meta->buf[i] == 40 || meta->buf[i] == 41 || meta->buf[i] == 60
			|| meta->buf[i] == 62 || meta->buf[i] == 32)
		{
			cmd->meta_char[j] = meta->buf[i];
			//meta->buf[i] = '\0';
			j += 1;
		}
		i++;
	}
}
