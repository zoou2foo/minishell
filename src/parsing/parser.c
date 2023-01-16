/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/16 13:10:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_meta	*metadata;	//our global var

t_cmd	*parse_cmd(char *cmdstr)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);

	if (cmdstr && cmdstr[0])
	{

	}
	return (cmd);
}

t_cmd_block	*parse_line(char *line)
{
	t_cmd_block	*cmdblock;
	char		**cmdstrs;
	int			i;

	cmdblock = ft_calloc(sizeof(t_cmd_block), 1);
	if (!cmdblock)
		return (NULL);

	if (line && line[0])
	{
		cmdstrs = ft_split(line, '|');
		cmdblock->cmds = ft_calloc(sizeof(t_cmd *), ft_count_char(line, '|') + 2);
		i = -1;
		while (cmdstrs[++i])
		{
			cmdblock->cmds[i] = parse_cmd(cmdstrs[i]);
		}
		cmdblock->is_empty = false;
		cmdblock->is_valid = true;
	}
	return (cmdblock);
}
