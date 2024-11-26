/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 14:41:06 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 17:07:27 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

int	error_input_checker(t_data *data, char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	data->exit_code = type;
	return (1);
}

int	error_unexpected_token(t_data *data, char *str, int type)
{
	int len;

	len = ft_strlen(str);
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 48);
	write(STDERR_FILENO, str, len);
	write(STDERR_FILENO, "'\n", 3);
	data->exit_code = type;
	return (1);
}

static int	special_redin_to_pipe(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 1)
	{
		while (str[i])
			i++;
		i--;
		while (ms_isspace(str[i]))
			i--;
		while (i > 0)
		{
			if (str[i] == '|' && str[i - 1] == '<')
				return (1);
			i--;
		}
	}
	return (0);
}

int	input_checker(t_data *data, char *line)
{
	char	*str1;

	str1 = "minishell: missing closing quotation marks\n";
	if (start_with_pipe(line) == 1 || redin_to_pipe(line) == 1)
		return (error_unexpected_token(data, "|", 2));
	if (special_redin_to_pipe(line) == 1)
		return (error_unexpected_token(data, "|", 2));
	if (pipe_at_end(line) == 1)
		return (error_unexpected_token(data, "newline", 2));
	if (redin_to_pipe(line) == 2)
		return (error_unexpected_token(data, "newline", 2));
	if (multiple_pipes(line) == 1)
		return (error_unexpected_token(data, "||", 2));
	if (missing_closing_q_marks(data->line) == 1)
		return (error_input_checker(data, str1, -1));
	if (multiple_redirections(data->line) == 1)
		return (error_unexpected_token(data, ">", 2));
	if (multiple_redirections(data->line) == 2)
		return (error_unexpected_token(data, "<", 2));
	if (unexpected_new_line(data->line) == 1)
		return (error_unexpected_token(data, "newline", 2));
	return (0);
}
