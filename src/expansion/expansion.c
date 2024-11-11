/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/11 16:59:34 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_stderror(t_data *data, int i)
{
	char	*temp;
	char	*substr;
	int		new_line;

	printf("1 - This is data->line: %s\n", data->line);
	substr = ft_substr(data->line, i + 2, ft_strlen(&data->line[i + 1]));
	temp = ft_substr(data->line, 0, i);
	data->exit_code = 200;
	new_line = ft_strlen(data->line) - 2 + ft_strlen(ft_itoa(data->exit_code));
	printf("This is new_line len: %i\n", new_line);
	printf("This is substring:%s\n", substr);
	printf("This is temp: %s\n", temp);
	free(data->line);
	printf("This is the len of exit_code: %zu\n", ft_strlen(ft_itoa(data->exit_code)));
	data->line = ft_calloc(sizeof(char),new_line); //I need the lenght of exit code.
	data->line = ft_strdup(temp);
	free (temp);
	char *exit_code = ft_itoa(data->exit_code);
	printf("Exit code len: %zu\n", ft_strlen(exit_code) + 1);
	ft_strlcat(data->line, exit_code, ft_strlen(data->line) + ft_strlen(exit_code) + 1);
	printf("2 - This is data->line: %s\n", data->line);
	ft_strlcat(data->line, substr, ft_strlen(data->line) + ft_strlen(substr) + 1);
	printf("3 - This is data->line: %s\n\n\n", data->line);
	free(substr);

}

void	expansion(t_data *data)
{
	int	i;

	i = 0;
	while(data->line[i])
	{
		// printf("data->line[%i]: %c\n", i, data->line[i]);
		if (data->line[i] == '$' && data->line[i + 1] == '?')
			expand_stderror(data, i);
		i++;
	}
}