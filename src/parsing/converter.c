/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/07 13:46:42 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	from token array

	create one t_cmd per line

	loop on all lines multiple times:
		- once to merge tokens (ex > type + string = string w/ type >)
		- once to fill the t_cmd with the redir (and call here*
		10
		doc funct)
		- once to convert remaining tokens into cmd_args

	free all tokens

	//AFTER WE SHOULD TEST/INTEGRATE THE BUILT-INS

*/

// : set the "has_pipes"
t_cmd	*tokens_to_cmd(t_token **head, int id)
{
	t_token	*node;
	int		i;
	t_cmd	*cmd;

	node = *head;
	while (node->next) //merge tokens (ex > type + string = string w/ type >)
	{
		if (node->next->type <= TTYPE_EXPAND && TTYPE_EXPAND < node->type)
			node = merge_tokens(node, node->next);
		if (node->next)
			node = node->next;
		else
			break;
	}

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->id = id;
	cmd->fdin = 0;	//set default fd to use later
	cmd->fdout = 1;	//set default fd to use later

	node = remove_empty_list(*head);
	while (node)	//MAKE THE INPUT OVERRIDE WORK PROPERLY WITH HEREDOCS
	{
		if (TTYPE_EXPAND < node->type)
		{

			if (node->type == TTYPE_S_RDR_OUT)
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = false;					//did I swap them??
			}
			else if (node->type == TTYPE_D_RDR_OUT)
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = true;					//did I swap them??
			}
			else if (node->type == TTYPE_REDIR_IN)
			{
				ft_free_null(cmd->input);
				cmd->input = ft_strdup(node->string);
				if (cmd->fdin != 0)
					close(cmd->fdin);
				cmd->fdin = 0;
			}
			else if (node->type == TTYPE_HEREDOC)
			{
				ft_free_null(cmd->input);
				if (cmd->fdin != 0)
					close(cmd->fdin);
				cmd->fdin = execute_hd(node->string);
			}
			node = cut_token(node);
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}
	*head = find_head(node);	//update head if cut destroys it

	//open input and output file if they exist			(PROTECT ME)
	if (cmd->input)		//close previous fd before opening new one !!!
		cmd->fdin = open(cmd->input, O_RDONLY);
	else if (!cmd->fdin && 0 < id)
		cmd->fdin = metadata->pipes[id - 1][0];

	if (cmd->output)	//close previous fd before opening new one !!!
	{
		if (cmd->append_output)
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_TRUNC, 0666);	//effectively 0644 because of umask);
	}
	else if (id < metadata->cmd_nb - 1)
		cmd->fdout = metadata->pipes[id][1];

	cmd->cmd_args = ft_calloc(find_length(*head) + 1, sizeof(char *));

	i = 0;
	node = *head;
	while (node)	//convert remaining tokens into cmd_args
	{
		if (node->type != TTYPE_EMPTY)
		{
			cmd->cmd_args[i++] = ft_strdup(node->string);
			cmd->argcount++;
		}
		node = node->next;
	}

	if (cmd->argcount > 0 && is_built_in(cmd->cmd_args[0]) == 1)
		cmd->is_built_in = true;
	else
		cmd->is_built_in = false;

	return (cmd);
}

void	load_cmd_block(t_token **head)
{
	int	i;


	i = 0;
	while (head[i])
		i++;
	metadata->cmd_block = ft_calloc(i + 1, sizeof(t_cmd *));	//MUST FREE CMD_BLOCK BEFOREHAND
	metadata->pipes = ft_calloc(i, sizeof(int *));
	metadata->cmd_nb = i;

	i = -1;
	while (++i < metadata->cmd_nb - 1)
	{
		metadata->pipes[i] = ft_calloc(2, sizeof(int));
		pipe(metadata->pipes[i]);								//FREE ME AT END OF CYCLE
	}

	i = -1;
	while (head[++i])
	{
		metadata->cmd_block[i] = tokens_to_cmd(&head[i], i);
	}
}
