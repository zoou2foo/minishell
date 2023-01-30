/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/01/30 16:54:50 by vjean            ###   ########.fr       */
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

t_cmd	*tokens_to_cmd(t_token **head, int id)		//TODO : set the "has_pipes"
{
	t_cmd	*cmd;
	t_token	*node;
	int		i;

	node = *head;
	while (node->next)	//merge tokens (ex > type + string = string w/ type >)
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

	node = *head;
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
			}
			else if (node->type == TTYPE_HEREDOC)
			{
				ft_free_null(cmd->input);
				//close previous heredoc if necessary
				//cmd->fdin = execute_hd(node->string);
			}
			if (node->next || node->prev)
				node = cut_token(node);
			else
				empty_token(node);
		}
		if (node->next)
			node = node->next;
		else
			break;
	}
	*head = find_head(node);	//update head if cut destroys it

	//open input and output file if they exist			(PROTECT ME)
	if (cmd->input)
		cmd->fdin = open(cmd->input, O_RDONLY);
	else if (!cmd->fdin && 0 < id)
		cmd->fdin = metadata->pipes[id - 1][1];

	if (cmd->output)
	{
		if (cmd->append_output)
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_TRUNC, 0666);	//effectively 0644 because of umask);
	}
	else if (id < metadata->cmd_nb - 1)
		cmd->fdout = metadata->pipes[id][0];

	cmd->argcount = find_length(*head);
	cmd->cmd_args = ft_calloc(cmd->argcount + 1, sizeof(char *));

	i = 0;
	node = *head;
	while (node)	//convert remaining tokens into cmd_args
	{
		cmd->cmd_args[i++] = ft_strdup(node->string);
		node = node->next;
	}

	return (cmd);
}

void	load_cmd_block(t_token **head)
{
	int	i;


	i = 0;
	while(head[i])
		i++;
	metadata->cmd_block = ft_calloc(i + 1, sizeof(t_cmd *));	//MUST FREE CMD_BLOCK BEFOREHAND
	metadata->pipes = ft_calloc(i, sizeof(int *));
	metadata->cmd_nb = i;

	i = -1;
	while(++i < metadata->cmd_nb - 1)
	{
		metadata->pipes[i] = ft_calloc(2, sizeof(int));
		pipe(metadata->pipes[i]);
	}

	i = -1;
	while(head[++i])
		metadata->cmd_block[i] = tokens_to_cmd(&head[i], i);
}