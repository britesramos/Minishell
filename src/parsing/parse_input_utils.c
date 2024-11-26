/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:18:20 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 13:32:18 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*p_pipe(t_token *current_t, t_data *data)
{
	current_t = current_t->next;
	data->nbr_pipes++;
	return (current_t);
}

t_token	*p_redirections(t_token *current_t, t_cmd *c_cmd, t_data *data)
{
	if (current_t->type == T_REIN)
		current_t = p_rein(current_t, c_cmd, data);
	else if (current_t->type == T_REOUT)
		current_t = p_reout(current_t, c_cmd, data);
	else if (current_t->type == T_APPEND)
		current_t = p_append(current_t, c_cmd, data);
	else if (current_t->type == T_HEREDOC)
	{
		if (c_cmd->infile)
			free_close_fd(c_cmd->infile, c_cmd->fd_in);
		current_t = p_heredoc(current_t, c_cmd, data);
		if (current_t == NULL && data->exit_code == 130)
			return (NULL);
	}
	return (current_t);
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

int	parse_input_help(t_data *data, t_token **c_t, t_cmd **c_cmd, int *i)
{
	while (*c_t && (*c_t)->type != T_PIPE && (*c_t)->lenght > 0)
	{
		if ((*c_t)->type != T_WORD && (*c_t)->type != T_PIPE)
		{
			*c_t = p_redirections(*c_t, *c_cmd, data);
			if (*c_t == NULL)
				return (9);
		}
		else if ((*c_t)->type == T_WORD && (*c_t)->type != T_PIPE)
			*i = p_word(*c_t, *c_cmd, data, *i);
		*c_t = (*c_t)->next;
	}
	return (0);
}
