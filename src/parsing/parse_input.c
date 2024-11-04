/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/04 12:33:26 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static t_token	*parse_rein(t_token *current_token, t_cmd *current_cmd, t_data *data)
{
	current_token = current_token->next;
	// if(current_token->type == T_WORD) //Fix tokenization first.
	if (current_cmd->infile)
		free_close_fd(current_cmd->infile, current_cmd->fd_in);
	current_cmd->fd_in = open(current_token->str, O_RDONLY);
	if (current_cmd->fd_in == -1)
		error_exit_system(data, current_token->str, 1);
	current_cmd->infile = ft_strdup(current_token->str);
	if(!current_cmd->infile)
		error_exit(data, NULL, "Infile red allocation failed!\n", 1); //Free memory.
	return (current_token);
}

static t_token	*parse_reout(t_token *current_token, t_cmd *current_cmd, t_data *data)
{
	current_token = current_token->next;
	if (current_cmd->outfile)
		free_close_fd(current_cmd->outfile, current_cmd->fd_out);
	current_cmd->fd_out = open(current_token->str, O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (current_cmd->fd_out == -1)
		error_exit_system(data, current_token->str, 1);
	current_cmd->outfile = ft_strdup(current_token->str);
	if(!current_cmd->outfile)
		error_exit(data, NULL, "Outfile red allocation failed!\n", 1); //Free memory.
	return (current_token);
}

static t_token 	*parse_append(t_token *current_token, t_cmd *current_cmd, t_data *data)
{
	current_cmd->append = true;
	current_token = current_token->next;
	if (current_cmd->outfile)
		free_close_fd(current_cmd->outfile, current_cmd->fd_out);
	current_cmd->fd_out = open(current_token->str, O_CREAT | O_APPEND | O_RDWR);
	if (current_cmd->fd_out == -1)
		error_exit_system(data, current_token->str, 1);
	current_cmd->outfile = ft_strdup(current_token->str);
	if(!current_cmd->outfile)
		error_exit(data, NULL, "Outfile Append allocation failed!\n", 1); //Free memory.
	return (current_token);
}

static int	parse_word(t_token *current_token, t_cmd *current_cmd, t_data *data, int i)
{
	int 	alloc_times = 2;

	// printf("alloc_times: %i - i: %i\n", alloc_times, i);
	if (current_cmd->cmd == NULL)
		current_cmd->cmd = (char **)ft_calloc(alloc_times + 1, sizeof(char *));
	if (!current_cmd->cmd)
		error_exit(data, NULL, "Error allocating word!\n", 1);
	if (i >= alloc_times)
	{
		// printf("HERE!\n");
		current_cmd->cmd = ft_realloc(data, 2 + i, current_cmd->cmd);
		alloc_times = 2;
	}
	if (alloc_times > 0)
	{
		current_cmd->cmd[i] = ft_strdup(current_token->str);
		alloc_times--;
		i++;
	}
	return (i);
}

void	parse_input(t_data *data, t_token *token_list)
{
	t_token *current_token;
	t_cmd	*current_cmd;
	t_cmd	*newnode;
	int 	i;

	current_token = token_list;
	current_cmd = data->cmd_head;
	while(current_token)
	{
		i = 0;
		newnode = create_new_node_cmd(data);
		add_new_node(&data->cmd_head, newnode, &current_cmd);
		while(current_token && current_token->type != T_PIPE)
		{
			if (current_token->type == T_REIN)
				current_token = parse_rein(current_token, current_cmd, data);
			else if (current_token->type == T_REOUT)
				current_token = parse_reout(current_token, current_cmd, data);
			else if (current_token->type == T_APPEND)
				current_token = parse_append(current_token, current_cmd, data);
			else if (current_token->type == T_WORD)
				i = parse_word(current_token, current_cmd, data, i);
			current_token = current_token->next;
		}
		if (current_token && current_token->type == T_PIPE)
		{
			current_token = current_token->next;
			data->nbr_pipes++;
		}
	}
}
