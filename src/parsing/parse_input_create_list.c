/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input_create_list.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/22 18:47:56 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 17:32:04 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*create_new_node_cmd(t_data *data)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		error_exit(data, NULL, "Memory allocation failed!", 1);
	node->cmd = NULL;
	node->fd_in = data->std[IN];
	node->fd_out = data->std[OUT];
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = NULL;
	node->heredoc = false;
	node->error = NULL;
	node->invalid_fd = false;
	return (node);
}

void	add_new_node(t_cmd **head, t_cmd *newnode, t_cmd **current_cmd)
{
	t_cmd	*temp;

	temp = NULL;
	if (*head == NULL)
	{
		*head = newnode;
		*current_cmd = newnode;
	}
	else
	{
		temp = *head;
		while (temp->pipe != NULL)
			temp = temp->pipe;
		temp->pipe = newnode;
		*current_cmd = temp->pipe;
	}
}
