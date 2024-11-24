/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_word_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 13:58:39 by anonymous     #+#    #+#                 */
/*   Updated: 2024/11/24 13:58:39 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	len_utils(t_data *data, int start)
{
	int		len;
	bool	sq;
	bool	dq;

	len = 0;
	sq = false;
	dq = false;
	while (data->line[start + len])
	{
		if (data->line[start + len] == '\'' && dq == false)
			sq = !sq;
		if (data->line[start + len] == '"' && sq == false)
			dq = !dq;
		if (ms_isspace(data->line[start + len]) && sq == false && dq == false)
			break ;
		if (data->line[start + len] == '|' && sq == false && dq == false)
			break ;
		len++;
	}
	return (len);
}

int	len_result(t_data *data, int start)
{
	int		len;

	len = 0;
	if (start == 0)
	{
		while (ms_isword(data->line[start + len])
			&& !ms_isspace(data->line[start + len]))
			len++;
	}
	else
	{
		if ((data->line[start] == '\'' || data->line[start] == '"')
			&& data->line[start + 1] == '\0')
			return (start + 1);
		else
			len = len_utils(data, start);
	}
	return (len);
}
