/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_word_remove_spaces.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/22 18:34:47 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/30 15:24:48 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_spaces(char *temp)
{
	int	i;
	int	spaces_c;

	i = 0;
	spaces_c = 0;
	while (temp[i])
	{
		if (ms_isspace(temp[i]) && ms_isspace(temp[i + 1]))
			spaces_c++;
		i++;
	}
	return (spaces_c);
}

static char	*remove_extra_spaces(char *new, char *temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (ms_isspace(temp[i]) && ms_isspace(temp[i + 1]))
			i++;
		if (!(ms_isspace(temp[i]) && ms_isspace(temp[i + 1])))
		{
			new[j] = temp[i];
			i++;
			j++;
		}
	}
	return (new);
}

char	*token_word_remove_extra_spaces(char *new, t_data *data)
{
	char	*temp;
	int		remove_c;

	temp = ft_strdup(new);
	if (!temp)
		error_exit(data, NULL, "Fail alloc temp in remove spaces", -10);
	free(new);
	new = NULL;
	remove_c = count_spaces(temp);
	new = ft_calloc(sizeof(char), ft_strlen(temp) - remove_c + 1);
	if (!new)
		error_exit(data, NULL, "Fail alloc in remove spaces", -10);
	new = remove_extra_spaces(new, temp);
	free(temp);
	return (new);
}
