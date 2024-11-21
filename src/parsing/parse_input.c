/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/21 12:12:30 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*p_rein(t_token *current_t, t_cmd *current_cmd, t_data *data)
{
	current_t = current_t->next;
	if (current_cmd->infile)
		free_close_fd(current_cmd->infile, current_cmd->fd_in);
	current_cmd->fd_in = open(current_t->str, O_RDONLY);
	if (current_cmd->fd_in == -1)
		error_exit_system(data, current_t->str, 1);
	current_cmd->infile = ft_strdup(current_t->str);
	if (!current_cmd->infile)
		error_exit(data, NULL, "Infile red allocation failed!\n", 1);
	return (current_t);
}

t_token	*p_reout(t_token *current_t, t_cmd *c_cmd, t_data *data)
{
	current_t = current_t->next;
	if (c_cmd->outfile)
		free_close_fd(c_cmd->outfile, c_cmd->fd_out);
	c_cmd->fd_out = open(current_t->str, O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (c_cmd->fd_out == -1)
		error_exit_system(data, current_t->str, 1);
	c_cmd->outfile = ft_strdup(current_t->str);
	if (!c_cmd->outfile)
		error_exit(data, NULL, "Outfile red allocation failed!\n", 1);
	return (current_t);
}

t_token	*p_append(t_token *current_t, t_cmd *current_cmd, t_data *data)
{
	current_t = current_t->next;
	if (current_cmd->outfile)
		free_close_fd(current_cmd->outfile, current_cmd->fd_out);
	current_cmd->fd_out = open(current_t->str, O_CREAT | O_APPEND | O_RDWR);
	if (current_cmd->fd_out == -1)
		error_exit_system(data, current_t->str, 1);
	current_cmd->outfile = ft_strdup(current_t->str);
	if (!current_cmd->outfile)
		error_exit(data, NULL, "Outfile Append allocation failed!\n", 1);
	return (current_t);
}

static int	p_word(t_token *current_t, t_cmd *current_cmd, t_data *data, int i)
{
	int	alloc_times;

	alloc_times = 2;
	if (current_cmd->cmd == NULL)
		current_cmd->cmd = (char **)ft_calloc(alloc_times + 1, sizeof(char *));
	printf("Current_cmd: %p\n", current_cmd->cmd);
	if (!current_cmd->cmd)
		error_exit(data, NULL, "Error allocating word!\n", 1);
	if (i >= alloc_times)
	{
		current_cmd->cmd = ft_realloc(data, 2 + i, current_cmd->cmd);
		alloc_times = 2;
	}
	if (alloc_times > 0)
	{
		current_cmd->cmd[i] = ft_strdup(current_t->str);
		if (!current_cmd->cmd[i])
		{
			if (current_cmd->cmd)
				ft_free_array(current_cmd->cmd);
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
	while (current_t && current_t->lenght > 0)
	{
		i = 0;
		newnode = create_new_node_cmd(data);
		add_new_node(&data->cmd_head, newnode, &current_cmd);
		while (current_t && current_t->type != T_PIPE && current_t->lenght > 0)
		{
			if (current_t->type != T_WORD && current_t->type != T_PIPE)
			{
				current_t = p_redirections(current_t, current_cmd, data);
				if (current_t == NULL)
					return (9);
			}
			else if (current_t->type == T_WORD && current_t->type != T_PIPE)
				i = p_word(current_t, current_cmd, data, i);
			current_t = current_t->next;
		}
		if (current_t && current_t->type == T_PIPE)
			current_t = p_pipe(current_t, data);
	}
	return (0);
}
