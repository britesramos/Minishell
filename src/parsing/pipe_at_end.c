/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_at_end.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/23 20:51:47 by anonymous     #+#    #+#                 */
/*   Updated: 2024/11/23 20:51:47 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_at_end(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
		i++;
	i--;
	while (is_space(data->line[i]))
		i--;
	printf("This data->line[%i]: %c\n", i, data->line[i]);
	if (data->line[i] == '|')
		return (1);
	return (0);
}

void	keep_reading_line(t_data *data)
{
	char	*temp;

	temp = NULL;
	temp = readline("> ");
	//signals
	ft_strlcat(data->line, temp, ft_strlen(temp) + ft_strlen(data->line) + 1);
}
