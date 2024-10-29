/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/29 12:56:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_cmd_list(t_cmd *list)
{
	while(list)
	{
		free (list);
		list = list->pipe;
	}
}

static t_cmd *create_new_node_cmd(t_data *data)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		error_exit(data, "Memory allocation failed!", 1);
	node->cmd = NULL;
	// node->append = false;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = NULL;
	
	return (node);
}

static char **ft_realloc(t_data *data, int number_of_times, char **old_array)
{
	char **new;
	int	i = 0;

	new = (char **)ft_calloc(number_of_times, sizeof(char *));
	if(!new)
		error_exit(data, "Memory calloc failed!\n", 1); //fix

	while (old_array[i])
	{
		new[i] = ft_strdup(old_array[i]);
		//Protect.
		i++;
	}
	while (i > 0)
	{
		free(old_array[i]);
		old_array[i] = NULL;
		i--;
	}
	free(old_array);
	old_array = NULL;
	return(new);
}

static void	parse_input2(t_data *data, t_token *token_list)
{
	t_token *current_token;
	t_cmd	*current_cmd;
	t_cmd	*newnode;
	int		i;
	int 	number_of_times_you_have_allocated;

	i = 0;
	number_of_times_you_have_allocated = 2;
	current_token = token_list;
	current_cmd = data->cmd_head;
	while(current_token)
	{
		newnode = create_new_node_cmd(data);
		if(current_cmd == NULL)
		{
			current_cmd = newnode;
			data->cmd_head = current_cmd;
		}
		else if(current_cmd != NULL)
		{
			while (current_cmd != NULL)
				current_cmd = current_cmd->pipe;
			current_cmd = newnode;
		}
		while(current_token && current_token->type != T_PIPE)
		{
			if (current_token->type == T_REIN)
			{
				current_token = current_token->next;
				// if(current_token->type == T_WORD) //Fix tokenization first.
				if (current_cmd->infile)
				{
					free(current_cmd->infile);
					close(current_cmd->fd_in);
				}
				current_cmd->fd_in = open(current_token->str, O_RDONLY);
				if (current_cmd->fd_in == -1)
				{
					error_exit(data, "BAAAAAAAAAA!\n", 1);
				}
					//syntax error infile does not exist
				current_cmd->infile = ft_strdup(current_token->str);
				if(!current_cmd->infile)
					error_exit(data, "Infile red allocation failed!\n", 1); //Free memory.
				// printf("RED IN: %s\n", current_cmd->infile);
			}
			else if (current_token->type == T_REOUT)
			{
				current_token = current_token->next;
				if (current_cmd->outfile)
				{
					free(current_cmd->outfile);
					close(current_cmd->fd_out);
				}
				current_cmd->fd_out = open(current_token->str, O_CREAT | O_TRUNC | O_RDWR);
				printf("This is token str: %s\n", current_token->str);
				// if (current_cmd->fd_out == -1)
				// 	//do something
				current_cmd->outfile = ft_strdup(current_token->str);
				printf("This is token str: %s\n", current_token->str);
				if(!current_cmd->outfile)
					error_exit(data, "Outfile red allocation failed!\n", 1); //Free memory.
				// printf("RED OUT: %s\n", current_cmd->outfile);
			}
			else if (current_token->type == T_APPEND)
			{
				// current_cmd->append = true;
				current_token = current_token->next;
				if (current_cmd->outfile)
				{
					free(current_cmd->outfile);
					close(current_cmd->fd_out);
				}
				current_cmd->fd_out = open(current_token->str, O_CREAT | O_APPEND | O_RDWR);
				current_cmd->outfile = ft_strdup(current_token->str);
				if (current_cmd->fd_out == -1)
					//do something
				if(!current_cmd->outfile)
					error_exit(data, "Outfile Append allocation failed!\n", 1); //Free memory.
				// printf("APPEND\n");
			}	
			else if (current_token->type == T_WORD)
			{
				// printf("HERE6!\n");
				if (current_cmd->cmd == NULL)
				{
					current_cmd->cmd = (char **)ft_calloc(number_of_times_you_have_allocated + 1, sizeof(char *));
				}
				if (number_of_times_you_have_allocated <= 0)
				{
					current_cmd->cmd = ft_realloc(data, 2 + i, current_cmd->cmd);
					number_of_times_you_have_allocated = 2;
				}
				if (number_of_times_you_have_allocated > 0)
				{
					// printf("%i\n", i);
					current_cmd->cmd[i] = ft_strdup(current_token->str);
					// printf("current_cmd->cmd[%i]: %s\n", i, current_cmd->cmd[i]);
					i++;
					number_of_times_you_have_allocated--;
				}
				// current_token = current_token->next;
			}
			current_token = current_token->next;
		}
		if (current_token && current_token->type == T_PIPE)
			current_token = current_token->next;
		// printf("ANOTHER PIPE!\n");
	}
}

void	parse_input(t_data *data, t_token *token_list)
{
	parse_input2(data, token_list);

	t_cmd *current = data->cmd_head;
	while (current)
	{
		int i = 0;
		while(current->cmd[i])
		{
			printf("This is cmd[0]: %s\n", current->cmd[i]);
			i++;
		}
		printf("This is fd_in: %i\n", current->fd_in);
		printf("This is fd_out: %i\n", current->fd_out);
		printf("This is infile: %s\n", current->infile);
		printf("This is outfile: %s\n", current->outfile);
		current = current->pipe;
	}

	free_cmd_list(data->cmd_head);
}
