/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 14:41:06 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/23 21:15:49 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	error_input_checker(t_data *data, char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	data->exit_code = type;
	return (1);
}

int	input_checker(t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	str1 = "minishell: syntax error near unexpected token `||'\n";
	str2 = "minishell: missing closing quotation marks\n";
	str3 = "minishell: syntax error near unexpected token `>'\n";
	str4 = "syntax error near unexpected token `newline'\n";
	while (pipe_at_end(data))
		keep_reading_line(data);
	if (start_with_pipe(data->line) == 1 || multiple_pipes(data->line) == 1)
		return (error_input_checker(data, str1, 2));
	if (missing_closing_q_marks(data->line) == 1)
		return (error_input_checker(data, str2, -1));
	if (multiple_redirection(data->line) == 1)
		return (error_input_checker(data, str3, 2));
	if (lonely_redirection(data->line) == 1)
		return (error_input_checker(data, str4, 2));
	return (0);
}
