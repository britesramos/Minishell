/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 14:17:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/24 19:50:36 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	multiple_redirections(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (1);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (2);
		i++;
	}
	return (0);
}

int	unexpected_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (ms_isspace(str[i]))
		i--;
	if (str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}
