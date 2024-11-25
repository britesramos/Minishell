/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 14:41:06 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 11:07:49 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	error_input_checker(t_data *data, char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	data->exit_code = type;
	return (1);
}

static int	error_unexpected_token(t_data *data, char *str, int type)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	data->exit_code = type;
	return (1);
}

int	input_checker(t_data *data, char *line)
{
	char	*str1;

	str1 = "minishell: missing closing quotation marks\n";
	if (start_with_pipe(line) == 1 || redin_to_pipe(line) == 1)
		return (error_unexpected_token(data, "|", 2));
	if (redin_to_pipe(line) == 2)
		return (error_unexpected_token(data, "newline", 2));
	if (multiple_pipes(line) == 1)
		return (error_unexpected_token(data, "||", 2));
	while (pipe_at_end(line))
		keep_reading_line(data);
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
