/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_heredoc.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 18:14:01 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_error(t_data *data, char *line, int i)
{
	char	*temp;
	char	*substr;
	char	*exit;
	int		new_line_len;
	int		sstr_len;

	exit = ft_itoa(data->exit_code);
	substr = ft_substr(line, i + 2, ft_strlen(&line[i + 1]));
	temp = ft_substr(line, 0, i);
	new_line_len = ft_strlen(line) - 2 + ft_strlen(exit);
	free(line);
	line = ft_calloc(sizeof(char), new_line_len + 1);
	if (!line)
		error_exit(data, NULL, "Failed alloc new line - expansion!\n", 1);
	ft_strlcpy(line, temp, ft_strlen(temp) + 1);
	free (temp);
	ft_strlcat(line, exit, ft_strlen(line) + ft_strlen(exit) + 1);
	free(exit);
	sstr_len = ft_strlen(substr);
	ft_strlcat(line, substr, ft_strlen(line) + sstr_len + 1);
	free(substr);
	return (line);
}

static char	*alloc_hd(t_data *data, char *temp, char *value, char *leftover)
{
	int	temp_i;
	int	value_i;
	int	lo_i;
	int	total;

	value_i = 0;
	lo_i = 0;
	total = 0;
	temp_i = ft_strlen(temp);
	if (value)
		value_i = ft_strlen(value);
	if (leftover)
		lo_i = ft_strlen(leftover);
	total = temp_i + value_i + lo_i;
	data->hd_line = ft_calloc(sizeof(char), total + 1);
	if (!data->hd_line)
		error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", 1);
	return (data->hd_line);
}

static char	*cat_line(char *line, char *value, char *leftover)
{
	if (value)
		ft_strlcat(line, value, ft_strlen(line) + ft_strlen(value) + 1);
	if (leftover)
	{
		ft_strlcat(line, leftover, ft_strlen(line) + ft_strlen(leftover) + 1);
		free(leftover);
	}
	return (line);
}

static char	*expand_path(t_data *data, char *line, int i)
{
	char	*temp;
	char	*substr;
	char	*leftover;
	char	*value;
	int		j;

	j = 0;
	leftover = NULL;
	temp = ft_substr(line, 0, i);
	i++;
	while (ft_isalnum(line[i + j]))
		j++;
	substr = ft_substr(line, i, j);
	value = find_value(data, substr);
	if (line[i + j])
		leftover = ft_substr(line, i + j,
				ft_strlen(line) - ft_strlen(substr) - ft_strlen(temp));
	free(substr);
	free(line);
	line = alloc_hd(data, temp, value, leftover);
	ft_strlcpy(line, temp, ft_strlen(temp) + 1);
	free(temp);
	line = cat_line(line, value, leftover);
	return (line);
}

char	*expansion_heredoc(t_data *data)
{
	int	i;

	i = 0;
	while (data->hd_line[i])
	{
		if (data->hd_line[i] == '$' && data->hd_line[i + 1] == '?')
			data->hd_line = expand_error(data, data->hd_line, i);
		else if (data->hd_line[i] == '$' && data->hd_line[i + 1])
			data->hd_line = expand_path(data, data->hd_line, i);
		i++;
	}
	return (data->hd_line);
}
