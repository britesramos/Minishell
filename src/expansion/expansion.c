/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 15:44:49 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/08 16:54:29 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_stderror(t_data *data, int i)
{
	char *temp;
	char *str = "A";
	// i = 0;
	// temp = NULL;
	
	temp = ft_strdup(data->line);
	ft_strlcpy(temp, temp, i + 1);
	ft_strlcat(temp, str, i + 1);
	printf("temp len: %zu\n", ft_strlen(temp));
	printf("This is temp: %s\n", temp);
	free(data->line);
	data->line = ft_calloc(sizeof(char),ft_strlen(temp) + 1/*ft_strlen(data->exit_code)*/); //I need the lenght of exist code.
	data->line = ft_strdup(temp);
	free (temp);
	data->exit_code = 200; //size of this. for the cat function.
	char *res = ft_itoa(data->exit_code);
	ft_strlcat(data->line, res, i + 10);
	printf("This is data->line: %s\n", data->line);


}

void	expansion(t_data *data)
{
	int	i;

	i = 0;
	while(data->line[i])
	{
		// printf("data->line[%i]: %c\n", i, data->line[i]);
		if (data->line[i] == '$' && data->line[i + 1] == '?')
		{
			expand_stderror(data, i);
			i++;
		}
		i++;
	}
}