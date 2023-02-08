/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:15:46 by vjean             #+#    #+#             */
/*   Updated: 2023/02/08 10:28:26 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert a single token list into a cmd, setting all info needed for execution
t_cmd	*tokens_to_cmd(t_token **head, int id)				// SPLIT ME UP SMH
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
	cmd->fdin = 0;		//set default fd to use later
	cmd->fdout = 1;		//set default fd to use later
	cmd->id = id;		//sets the id of the

	node = remove_empty_list(*head);	//remove all the empty tokens (except if its the only one left)

	//finds redirection nodes and uses them
	while (node)
	{
		if (TTYPE_EXPAND < node->type)
		{
			if (node->type == TTYPE_S_RDR_OUT)			// >
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = false;					//did I swap them??
			}
			else if (node->type == TTYPE_D_RDR_OUT)		// >>
			{
				ft_free_null(cmd->output);
				cmd->output = ft_strdup(node->string);
				cmd->append_output = true;					//did I swap them??
			}
			else if (node->type == TTYPE_REDIR_IN)		// <
			{
				ft_free_null(cmd->input);
				cmd->input = ft_strdup(node->string);
				if (cmd->fdin != 0)
					close(cmd->fdin);
				cmd->fdin = 0;
			}
			else if (node->type == TTYPE_HEREDOC)		// <<
			{
				ft_free_null(cmd->input);
				if (cmd->fdin != 0)
					close(cmd->fdin);
				cmd->fdin = execute_hd(node->string);
			}
			node = cut_token(node);						//remove node once used
		}
		if (node->next)
			node = node->next;
		else
			break ;
	}


	*head = find_head(node);	//reset head in case cut_token() destroys it

	//open input and output file if they exist		(PROTECT ME WITH ACCESS)
	if (cmd->input)									//opens the input file if it exists
		cmd->fdin = open(cmd->input, O_RDONLY);
	else if (!cmd->fdin && 0 < id)					//else, uses the pipe if it can AND has no heredoc pipe set already
		cmd->fdin = metadata->pipes[id - 1][0];

	if (cmd->output)								//opens the output file if it exists
	{
		if (cmd->append_output)
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_APPEND, 0666);	//effectively 0644 because of umask);
		else
			cmd->fdout = open(cmd->output, O_CREAT | O_RDWR | O_TRUNC, 0666);	//effectively 0644 because of umask);
	}
	else if (id < metadata->cmd_nb - 1)				//else, uses the pipe if it can
		cmd->fdout = metadata->pipes[id][1];


	node = *head;		//reset node

	cmd->cmd_args = ft_calloc(find_length(node) + 1, sizeof(char *));

	i = 0;
	while (node)		//convert remaining tokens into cmd_args
	{
		if (node->type != TTYPE_EMPTY)
		{
			cmd->cmd_args[i++] = ft_strdup(node->string);
			cmd->argcount++;
		}
		node = node->next;
	}


	//activates is_built_in if the cmd has at least 1 argument AND it is a built in
	if (cmd->argcount > 0 && is_built_in(cmd->cmd_args[0]) == 1)
		cmd->is_built_in = true;
	else
		cmd->is_built_in = false;

	return (cmd);
}

//converts every token list into cmds, setting all info needed for execution
void	load_cmd_block(t_token **head)
{
	int	i;


	i = 0;
	while (head[i])
		i++;
	metadata->cmd_block = ft_calloc(i + 1, sizeof(t_cmd *));	//FREE ME AT END OF CYCLE
	metadata->pipes = ft_calloc(i, sizeof(int *));
	metadata->cmd_nb = i;

	i = -1;
	while (++i < metadata->cmd_nb - 1)		//creates potentially needed pipes
	{
		metadata->pipes[i] = ft_calloc(2, sizeof(int));
		pipe(metadata->pipes[i]);								//FREE ME AT END OF CYCLE
	}

	i = -1;
	while (head[++i])		//actual token list conversion
	{
		metadata->cmd_block[i] = tokens_to_cmd(&head[i], i);
	}
}
