/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 14:41:06 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/14 17:19:36 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

static int	multiple_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

static int	missing_closing_q_marks(char *str)
{
	int		i;
	bool	single_q;
	bool	double_q;

	i = 0;
	single_q = true;
	double_q = true;
	while (str[i])
	{
		if (str[i] == '"' && single_q == true)
			double_q = !double_q;
		else if (str[i] == '\'' && double_q == true)
			single_q = !single_q;
		i++;
	}
	if (single_q == false || double_q == false)
		return (1);
	return (0);
}

static int	multiple_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (1);
		i++;
	}
	return (0);
}

static int	lonely_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '>' && str[i - 2] == '$')
		return (1);
	i = 0;
	if (str[i] == '$' && str[i + 1] == '>')
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
		return (1);
	else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0'))
		return (1);
	else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
		return (1);
	return (0);
}

/*Make something cleaner for all this returns! This doesnt look nice!*/
int	input_checker(t_data *data)
{
	if (start_with_pipe(data->line) == 1 || multiple_pipes(data->line) == 1)
	{
		error_exit(data, NULL, "minishell: syntax error near unexpected token `||'\n", 2);
		return (1);
	}
	if (missing_closing_q_marks(data->line) == 1)
	{
		error_exit(data, NULL, "minishell: missing closing quotation marks\n", -1);
		return (1);
	}
	if (multiple_redirection(data->line) == 1)
	{
		error_exit(data, NULL, "minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	if (lonely_redirection(data->line) == 1)
	{
		error_exit(data, NULL, "syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
