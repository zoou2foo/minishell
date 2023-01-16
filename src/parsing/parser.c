/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/16 15:19:44 by llord            ###   ########.fr       */
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

	cmd->cmd_args = ft_calloc(1, sizeof(char *));
	if (cmdstr && cmdstr[0])
	{
		//somehow get the redirections out first

		cmd->cmd_args[0] = ft_strdup(cmdstr);	//DEBUG ONLY

		//split remaining args along spaces (safe for ""/'')
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

		//FALSE, thsi doesn't acount for heredocs being commands
		cmdblock->cmd_count = ft_count_char(line, '|') + 1;

		cmdblock->cmds = ft_calloc(cmdblock->cmd_count + 1, sizeof(t_cmd *));
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
