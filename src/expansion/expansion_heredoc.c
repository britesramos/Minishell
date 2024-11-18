/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_heredoc.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/18 17:24:40 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_error(t_data *data, char *heredoc_line, int i)
{
	char	*temp;
	char	*substr;
	char	*exit;
	int		new_line_len;
	int		sstr_len;

	exit = ft_itoa(data->exit_code);
	substr = ft_substr(heredoc_line, i + 2, ft_strlen(&heredoc_line[i + 1]));
	temp = ft_substr(heredoc_line, 0, i);
	new_line_len = ft_strlen(heredoc_line) - 2 + ft_strlen(exit);
	free(heredoc_line);
	heredoc_line = ft_calloc(sizeof(char), new_line_len + 1);
	if (!heredoc_line)
		error_exit(data, NULL, "Failed alloc new line - expansion!\n", 1);
	ft_strlcpy(heredoc_line, temp, ft_strlen(temp) + 1);
	free (temp);
	ft_strlcat(heredoc_line, exit, ft_strlen(heredoc_line) + ft_strlen(exit) + 1);
	free(exit);
	sstr_len = ft_strlen(substr);
	ft_strlcat(heredoc_line, substr, ft_strlen(heredoc_line) + sstr_len + 1);
	free(substr);
	return (heredoc_line);
	printf("EXPAND ERROR: This is HEREDOC_LINE expansion: %s\n", heredoc_line);
}

static char *alloc_newline(t_data *data, char *heredoc_line, char *temp, char *value, char *leftover)
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
			heredoc_line = ft_calloc(sizeof(char), temp_i + value_i + lo_i + 1);
		else if (!leftover)
			heredoc_line = ft_calloc(sizeof(char), temp_i + value_i + 1);
		if (!heredoc_line)
			error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", 1);
	}
	if (!value)
	{
		if (leftover)
			heredoc_line = ft_calloc(sizeof(char), temp_i + lo_i + 1);
		else if (!leftover)
			heredoc_line = ft_calloc(sizeof(char), temp_i + 1);
		if (!heredoc_line)
			error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", 1);
	}
	return (heredoc_line);
}

static char	*expand_path(t_data *data, char *heredoc_line, int i)
{
	char	*temp;
	char	*substr;
	char	*leftover;
	char	*value;
	int		j;

	j = 0;
	leftover = NULL;
	temp = ft_substr(heredoc_line, 0, i);
	i++;
	while (ft_isalnum(heredoc_line[i + j]))
		j++;
	substr = ft_substr(heredoc_line, i, j);
	if (heredoc_line[i + j])
		leftover = ft_substr(heredoc_line, i + j, ft_strlen(heredoc_line) - ft_strlen(substr) - ft_strlen(temp));
	free(heredoc_line);
	value = find_value(data, substr);
	free(substr);
	heredoc_line = alloc_newline(data, heredoc_line, temp, value, leftover);
	ft_strlcpy(heredoc_line, temp, ft_strlen(temp) + 1);
	free(temp);
	if (value)
		ft_strlcat(heredoc_line, value, ft_strlen(heredoc_line) + ft_strlen(value) + 1);
	if (leftover)
	{
		ft_strlcat(heredoc_line, leftover, ft_strlen(heredoc_line) + ft_strlen(leftover) + 1);
		free(leftover);
	}
	return (heredoc_line);
}

char	*expansion_heredoc(t_data *data, char *heredoc_line)
{
	int	i;

	i = 0;
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '$' && heredoc_line[i + 1] == '?')
		{
			heredoc_line = expand_error(data, heredoc_line, i);
			printf("HOLA:This is HEREDOC_LINE expansion: %s\n", heredoc_line);
		}
		else if (heredoc_line[i] == '$' && heredoc_line[i + 1])
			heredoc_line = expand_path(data, heredoc_line, i);
		i++;
	}
	return (heredoc_line);
	printf("This is HEREDOC_LINE expansion: %s\n", heredoc_line);
}
