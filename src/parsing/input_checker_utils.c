/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 14:17:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/19 14:59:19 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	multiple_pipes(char *str)
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

int	missing_closing_q_marks(char *str)
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

int	multiple_redirection(char *str)
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

int	lonely_redirection(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[i + 1] == '\0')
		return (1);
	while (str[i])
		i++;
	if ((str[i - 1] == '>' && str[i - 2] == '$'))
		return (1);
	i = 0;
	if (str[i] == '$' && str[i + 1] == '>')
		return (1);
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
		return (1);
	else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0'))
		return (1);
	else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
		return (1);
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		return (1);
	return (0);
}
