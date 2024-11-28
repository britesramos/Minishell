/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/28 14:44:07 by sramos        ########   odam.nl         */
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

	exit = convert_exit_code(data);
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
	free(exit);
	sstr_len = ft_strlen(substr);
	ft_strlcat(data->line, substr, ft_strlen(data->line) + sstr_len + 1);
	free(substr);
}

static int	expand_path(t_data *data, int i)
{
	char	*temp;
	char	*substr;
	char	*leftover;
	char	*value;
	int		j;

	j = 0;
	leftover = NULL;
	value = NULL;
	temp = ft_substr(data->line, 0, i);
	i++;
	while (ft_isalnum(data->line[i + j]) || data->line[i + j] == '_')
		j++;
	substr = ft_substr(data->line, i, j);
	if (data->line[i + j])
		leftover = ft_substr(data->line, i + j,
				ft_strlen(data->line) - ft_strlen(substr) - ft_strlen(temp));
	free(data->line);
	value = find_value(data, substr);
	free(substr);
	alloc_newline(data, temp, value, leftover);
	ft_strlcpy(data->line, temp, ft_strlen(temp) + 1);
	free(temp);
	concatenate_newline(data, value, leftover);
	return (0);
}

static int	expand_path_digit(t_data *data, int i)
{
	char	*temp;
	char	*leftover;
	int		j;

	j = 2;
	leftover = NULL;
	temp = ft_substr(data->line, 0, i);
	i = i + 2;
	if (data->line[i])
		leftover = ft_substr(data->line, i,
				ft_strlen(data->line) - ft_strlen(temp) - 2);
	free(data->line);
	expand_path_digit_alloc(data, temp, leftover);
	ft_strlcpy(data->line, temp, ft_strlen(temp) + 1);
	free(temp);
	if (leftover)
	{
		ft_strlcat(data->line, leftover,
			ft_strlen(data->line) + ft_strlen(leftover) + 1);
		free(leftover);
	}
	return (0);
}

static int	expansion_helper(t_data *data, int i)
{
	if (data->line[i] == '"' && data->line[i + 1] == '$'
		&& data->line[i + 2] == '"')
		i = i + 3;
	else if (data->line[i] == '$' && data->line[i + 1] == '?')
		expand_error(data, i);
	else if (data->line[i] == '$' && ft_isdigit(data->line[i + 1]))
		expand_path_digit(data, i);
	else if (data->line[i] == '$'
		&& (ft_isalnum(data->line[i + 1]) || data->line[i + 1] == '_'))
	{
		expand_path(data, i);
		i--;
	}
	return (i);
}

void	expansion(t_data *data)
{
	int		i;
	bool	sq;
	bool	dq;

	i = 0;
	sq = false;
	dq = false;
	while (data->line[i])
	{
		if (data->line[i] == '\'' && dq == false)
			sq = !sq;
		else if (data->line[i] == '"' && sq == false)
			dq = !dq;
		if (data->line[i] == '\'' && dq == false)
		{
			i++;
			while (data->line[i] != '\'')
				i++;
		}
		i = expansion_helper(data, i);
		if (!data->line[i])
			break ;
		i++;
	}
}
