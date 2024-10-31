/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:18:20 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/31 15:26:43 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_close_fd(char *file, int fd)
{
	free(file);
	close(fd);
}

char **ft_realloc(t_data *data, int number_of_times, char **old_array)
{
	char **new;
	int	i = 0;

	new = (char **)ft_calloc(number_of_times, sizeof(char *));
	if(!new)
		error_exit(data, NULL, "Memory calloc failed!\n", 1); //fix

	while (old_array[i])
	{
		new[i] = ft_strdup(old_array[i]);
		//Protect.
		free(old_array[i]);
		old_array[i] = NULL;
		i++;
	}
	// while (i > 0)
	// {
	// 	free(old_array[i]);
	// 	old_array[i] = NULL;
	// 	i--;
	// }
	free(old_array);
	old_array = NULL;
	return(new);
}

t_cmd *create_new_node_cmd(t_data *data)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		error_exit(data, NULL, "Memory allocation failed!", 1);
	node->cmd = NULL;
	node->append = false;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = NULL;
	// if (node->pipe == NULL)
	// 	printf("HERE\n");
	return (node);
}

void	add_new_node(t_cmd **head, t_cmd *newnode, t_cmd **current_cmd)
{
	if (*head == NULL)
    {
        *head = newnode;
        *current_cmd = newnode;
    }
    else
    {
        t_cmd *temp = *head;
        while (temp->pipe != NULL) // Traverse to the end of the list
            temp = temp->pipe;
        temp->pipe = newnode; // Link the new node to the end
        *current_cmd = temp->pipe; // Update current_cmd to point to the new node
    }
}