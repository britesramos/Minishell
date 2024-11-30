/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/22 16:58:24 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/30 14:23:38 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_path_digit_alloc(t_data *data, char *temp, char *leftover)
{
	int	temp_len;
	int	leftover_len;

	temp_len = 0;
	leftover_len = 0;
	temp_len = ft_strlen(temp);
	if (leftover)
	{
		leftover_len = ft_strlen(leftover);
		data->line = ft_calloc(sizeof(char), temp_len + leftover_len + 1);
	}
	else
		data->line = ft_calloc(sizeof(char), temp_len + 1);
	if (!data->line)
		error_exit(data, NULL, "Fail alloc expand_path_digit!\n", -10);
}

void	concatenate_newline(t_data *data, char *value, char *leftover)
{
	int	value_len;
	int	leftover_len;

	value_len = 0;
	leftover_len = 0;
	if (value)
	{
		value_len = ft_strlen(data->line) + ft_strlen(value) + 1;
		ft_strlcat(data->line, value, value_len);
	}
	if (leftover)
	{
		leftover_len = ft_strlen(data->line) + ft_strlen(leftover) + 1;
		ft_strlcat(data->line, leftover, leftover_len);
		ft_free_string(&leftover);
	}
}

char	*convert_exit_code(t_data *data)
{
	int		exit_code;
	char	*exit;

	exit_code = 0;
	if (data->exit_code > 255)
	{
		exit_code = data->exit_code / 256;
		data->exit_code = exit_code;
	}
	else if (data->exit_code < -255)
		data->exit_code = data->exit_code % -256;
	else if (data->exit_code < 0)
		data->exit_code = data->exit_code + 256;
	exit = ft_itoa(data->exit_code);
	return (exit);
}

void	alloc_newline(t_data *data, char *temp, char *value, char *leftover)
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
	}
	if (!value)
	{
		if (leftover)
			data->line = ft_calloc(sizeof(char), temp_i + lo_i + 1);
		else if (!leftover)
			data->line = ft_calloc(sizeof(char), temp_i + 1);
	}
	if (!data->line)
		error_exit(data, NULL, "Fail alloc new_line | expand_path.\n", -10);
}
