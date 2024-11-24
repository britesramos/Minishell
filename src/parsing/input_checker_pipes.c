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

int	start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '|' && str[i + 1] != '|')
		return (1);
	return (0);
}

int	redin_to_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (ms_isspace(str[i]))
		i--;
	if (str[i] == '|' && str[i - 1] == '<')
		return (1);
	if (str[i] == '|' && str[i - 1] == '>')
		return (2);
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

int	pipe_at_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (is_space(line[i]))
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

void	keep_reading_line(t_data *data)
{
	char	*temp;

	temp = NULL;
	temp = readline("> ");
	// if (input_checker(data, temp) != 0)
	// 	return ;
	// ms_signals(HEREDOC); //Needs to be fixed.
	ft_strlcat(data->line, temp, ft_strlen(temp) + ft_strlen(data->line) + 1);
}
