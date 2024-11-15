/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/15 14:21:51 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_error(t_data *data, int i)
{
	char	*temp;
	char	*substr;
	char	*exit;
	int		new_line_len;
	int		sstr_len;

	exit = ft_itoa(data->exit_code);
	substr = ft_substr(data->line, i + 2, ft_strlen(&data->line[i + 1]));
	temp = ft_substr(data->line, 0, i);
	new_line_len = ft_strlen(data->line) - 2 + ft_strlen(exit);
	free(data->line);
	data->line = ft_calloc(sizeof(char), new_line_len + 1);
	if (!data->line)
		error_exit(data, NULL, "Failed alloc new line - expansion!\n", 1);
	ft_strlcpy(data->line, temp, ft_strlen(temp) + 1);
	free (temp);
	ft_strlcat(data->line, exit, ft_strlen(data->line) + ft_strlen(exit) + 1);
	sstr_len = ft_strlen(substr);
	ft_strlcat(data->line, substr, ft_strlen(data->line) + sstr_len + 1);
	free(substr);
}

static void	alloc_newline(t_data *data, char *temp, char *value, char *leftover)
{
	int	temp_i;
	int	value_i;
	int	lo_i;

	temp_i = ft_strlen(temp);
	if (value)
		value_i = ft_strlen(value);
	if (leftover)
		lo_i = ft_strlen(leftover);
	if (value)
	{
		if (leftover)
			data->line = ft_calloc(sizeof(char), temp_i + value_i + lo_i + 1);
		else if (!leftover)
			data->line = ft_calloc(sizeof(char), temp_i + value_i + 1);
		if (!data->line)
			error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", 1);
	}
	if (!value)
	{
		if (leftover)
			data->line = ft_calloc(sizeof(char), temp_i + lo_i + 1);
		else if (!leftover)
			data->line = ft_calloc(sizeof(char), temp_i + 1);
		if (!data->line)
			error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", 1);
	}
}

static void	expand_path(t_data *data, int i)
{
	char	*temp;
	char	*substr;
	char	*leftover;
	char	*value;
	int		j;

	j = 0;
	leftover = NULL;
	temp = ft_substr(data->line, 0, i);
	i++;
	while (ft_isalnum(data->line[i + j]))
		j++;
	substr = ft_substr(data->line, i, j);
	if (data->line[i + j])
		leftover = ft_substr(data->line, i + j, ft_strlen(data->line) - ft_strlen(substr) - ft_strlen(temp));
	free(data->line);
	value = find_value(data, substr);
	free(substr);
	alloc_newline(data, temp, value, leftover);
	ft_strlcpy(data->line, temp, ft_strlen(temp) + 1);
	free(temp);
	if (value)
		ft_strlcat(data->line, value, ft_strlen(data->line) + ft_strlen(value) + 1);
	if (leftover)
		ft_strlcat(data->line, leftover, ft_strlen(data->line) + ft_strlen(leftover) + 1);
	free(leftover);
}

void	expansion(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '$' && data->line[i + 1] == '?')
			expand_error(data, i);
		else if (data->line[i] == '$' && data->line[i + 1])
			expand_path(data, i);
		i++;
	}
}
