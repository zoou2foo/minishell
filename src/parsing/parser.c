/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:06:47 by llord             #+#    #+#             */
/*   Updated: 2023/01/23 08:40:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_meta	*metadata;	//our global var
/*

//=========( CMDER )=========//

//=========( NODER )=========//

t_cmd	*parse_cmd(char *cmdstr)
{

}
*/

//========( BLOCKER )========//

//appends cmdnode(s) to the given cmdblock (normally one except if heredoc)
void	add_cmds(void)//t_cmd_block *cmdblock, char *cmdstr)
{
	//TOKENIZE FIRST ARGGGG

	/*
	<< < << < cmd args >> > >>

	look for heredocs and append them as cmds, then discard them
	(empty cmd with is_heredoc and has_outpipe set to true)
	also remove redirections before heredocs
	( << | << | ) < cmd args >> > >>

	set input and output to last encountered values and discard them
	cmd args

	set remainder as cmd_args (keep ""/'' intact and aply changes in "${}")
		(use parse cmd)
	*/

}


//splits the cmd line along pipes and
t_cmd_block	*parse_line(char *line)
{
	t_cmd_block	*cmdblock;
	char		**cmdstrs;
	int			i;

	cmdblock = ft_calloc(sizeof(t_cmd_block), 1);

	if (line && line[0])
	{
		cmdstrs = ft_split(line, '|');
		cmdblock->cmd_count = ft_count_char(line, '|') + 1;
		//remember to update cmd_count when dealing with heredocs later

		i = -1;
		while (cmdstrs[++i])
		{
			add_cmds();//cmdblock, cmdstrs[i]);
		}
		cmdblock->cmds = ft_calloc(cmdblock->cmd_count + 1, sizeof(t_cmd *));

		//fill cmds with the cmds in the cmdnode list
	}
	return (cmdblock);
}
