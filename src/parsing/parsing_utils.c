/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:12:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/14 11:31:59 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	only_spaces(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (!is_space(data->line[i]))
			return (0);
		i++;
	}
	return (1);
}
