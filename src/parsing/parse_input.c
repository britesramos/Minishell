/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 13:32:16 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*p_rein(t_token *current_t, t_cmd *current_c, t_data *data)
{
	current_t = current_t->next;
	if (current_c->infile)
		free_close_fd(current_c->infile, current_c->fd_in);
	current_c->fd_in = open(current_t->str, O_RDONLY);
	if (current_c->fd_in == -1 && data->invalid_fd == false)
	{
		data->invalid_fd = true;
		error_exit_system(data, current_t->str, current_c, 1);
	}
	current_c->infile = ft_strdup(current_t->str);
	if (!current_c->infile)
		error_exit(data, NULL, "Infile red allocation failed!\n", 1);
	return (current_t);
}

t_token	*p_reout(t_token *current_t, t_cmd *current_c, t_data *data)
{
	current_t = current_t->next;
	if (current_c->outfile)
		free_close_fd(current_c->outfile, current_c->fd_out);
	current_c->fd_out = open(current_t->str, O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (current_c->fd_out == -1)
		error_exit_system(data, current_t->str, current_c, 1);
	current_c->outfile = ft_strdup(current_t->str);
	if (!current_c->outfile)
		error_exit(data, NULL, "Outfile red allocation failed!\n", 1);
	return (current_t);
}

t_token	*p_append(t_token *current_t, t_cmd *current_c, t_data *data)
{
	current_t = current_t->next;
	if (current_c->outfile)
		free_close_fd(current_c->outfile, current_c->fd_out);
	current_c->fd_out = open(current_t->str, O_CREAT | O_APPEND | O_RDWR, 0660);
	if (current_c->fd_out == -1)
		error_exit_system(data, current_t->str, current_c, 1);
	current_c->outfile = ft_strdup(current_t->str);
	if (!current_c->outfile)
		error_exit(data, NULL, "Outfile Append allocation failed!\n", 1);
	return (current_t);
}

int	p_word(t_token *current_t, t_cmd *current_c, t_data *data, int i)
{
	int	alloc_times;

	alloc_times = 2;
	if (current_c->cmd == NULL)
		current_c->cmd = (char **)ft_calloc(alloc_times + 1, sizeof(char *));
	if (!current_c->cmd)
		error_exit(data, NULL, "Error allocating word!\n", 1);
	if (i >= alloc_times)
	{
		current_c->cmd = ft_realloc(data, 2 + i, current_c->cmd);
		alloc_times = 2;
	}
	if (alloc_times > 0)
	{
		current_c->cmd[i] = ft_strdup(current_t->str);
		if (!current_c->cmd[i])
		{
			if (current_c->cmd)
				ft_free_array(current_c->cmd);
			error_exit(data, NULL, "Fail alloc new cmd array in parsing.\n", 1);
		}
		alloc_times--;
		i++;
	}
	return (i);
}

int	parse_input(t_data *data, t_token *token_list)
{
	int		i;
	t_token	*current_t;
	t_cmd	*current_cmd;
	t_cmd	*newnode;

	current_t = token_list;
	current_cmd = data->cmd_head;
	if ((current_t && current_t->lenght == 0) || !token_list)
		return (9);
	while (current_t && current_t->lenght > 0)
	{
		i = 0;
		newnode = create_new_node_cmd(data);
		add_new_node(&data->cmd_head, newnode, &current_cmd);
		if (parse_input_help(data, &current_t, &current_cmd, &i) == 9)
			return (9);
		if (current_t && current_t->type == T_PIPE)
			current_t = p_pipe(current_t, data);
	}
	data->cmd_current = data->cmd_head;
	return (0);
}
