/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/30 14:32:12 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*p_rein(t_token *token, t_cmd *current_c, t_data *data)
{
	token = token->next;
	if (current_c->infile)
		free_close_fd(current_c->infile, current_c->fd_in);
	if (current_c->invalid_fd_in == false && current_c->invalid_fd_out == false)
		current_c->fd_in = open(token->str, O_RDONLY);
	if (current_c->fd_in == -1 && current_c->invalid_fd_in == false)
	{
		current_c->invalid_fd_in = true;
		error_exit_system(data, token->str, current_c, 1);
	}
	current_c->infile = ft_strdup(token->str);
	if (!current_c->infile)
		error_exit(data, NULL, "Infile red allocation failed!\n", -10);
	return (token);
}

t_token	*p_reout(t_token *token, t_cmd *current_c, t_data *data)
{
	token = token->next;
	if (token->type == T_PIPE)
		token = token->next;
	if (current_c->outfile)
		free_close_fd(current_c->outfile, current_c->fd_out);
	if (current_c->invalid_fd_out == false && current_c->invalid_fd_in == false)
		current_c->fd_out = open(token->str, O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (current_c->fd_out == -1)
	{
		current_c->invalid_fd_out = true;
		error_exit_system(data, token->str, current_c, 1);
	}
	current_c->outfile = ft_strdup(token->str);
	if (!current_c->outfile)
		error_exit(data, NULL, "Outfile red allocation failed!\n", -10);
	return (token);
}

t_token	*p_append(t_token *token, t_cmd *current_c, t_data *data)
{
	token = token->next;
	if (current_c->outfile)
		free_close_fd(current_c->outfile, current_c->fd_out);
	if (current_c->invalid_fd_out == false)
		current_c->fd_out = open(token->str, O_CREAT | O_APPEND | O_RDWR, 0660);
	if (current_c->fd_out == -1)
	{
		current_c->invalid_fd_out = true;
		error_exit_system(data, token->str, current_c, 1);
	}
	current_c->outfile = ft_strdup(token->str);
	if (!current_c->outfile)
		error_exit(data, NULL, "Outfile Append allocation failed!\n", -10);
	return (token);
}

int	p_word(t_token *token, t_cmd *current_c, t_data *data, int i)
{
	int	alloc_times;

	alloc_times = 2;
	if (current_c->cmd == NULL)
		current_c->cmd = (char **)ft_calloc(alloc_times + 1, sizeof(char *));
	if (!current_c->cmd)
		error_exit(data, NULL, "Error allocating word!\n", -10);
	if (i >= alloc_times)
	{
		current_c->cmd = ft_realloc(data, 2 + i, current_c->cmd);
		alloc_times = 2;
	}
	if (alloc_times > 0)
	{
		current_c->cmd[i] = ft_strdup(token->str);
		if (!current_c->cmd[i])
		{
			if (current_c->cmd)
				ft_free_array(current_c->cmd);
			error_exit(data, NULL, "Fail alloc cmd array in parsing.\n", -10);
		}
		alloc_times--;
		i++;
	}
	return (i);
}

int	parse_input(t_data *data, t_token *token_list)
{
	int		i;
	t_token	*token;
	t_cmd	*current_cmd;
	t_cmd	*newnode;

	token = token_list;
	current_cmd = data->cmd_head;
	if ((token && token->lenght == 0) || !token_list)
		return (9);
	while (token && token->lenght > 0)
	{
		i = 0;
		newnode = create_new_node_cmd(data);
		add_new_node(&data->cmd_head, newnode, &current_cmd);
		if (parse_input_help(data, &token, &current_cmd, &i) == 8)
			return (8);
		if (token && token->type == T_PIPE)
			token = p_pipe(token, data);
	}
	data->cmd_current = data->cmd_head;
	return (0);
}
