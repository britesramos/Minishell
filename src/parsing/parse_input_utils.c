/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:18:20 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/18 17:59:38 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_null_2d_array(char **str)
{
	free(str);
	str = NULL;
}

static void	free_null_array(char *str)
{
	free(str);
	str = NULL;
}

char	**ft_realloc(t_data *data, int number_of_times, char **old_array)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)ft_calloc(number_of_times, sizeof(char *));
	if (!new)
		error_exit(data, NULL, "Memory calloc failed!\n", 1);
	if (old_array)
	{
		while (old_array[i])
		{
			new[i] = ft_strdup(old_array[i]);
			if (!new[i])
				error_exit(data, NULL, "Mem alloc failed - ft_realloc\n", 1);
			i++;
		}
		while (i >= 0)
		{
			free_null_array(old_array[i]);
			i--;
		}
		if (old_array)
			free_null_2d_array(old_array);
	}
	return (new);
}

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
