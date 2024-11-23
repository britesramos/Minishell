/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_word_remove_quotes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:02:12 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/22 18:34:45 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_quotes(char *str)
{
	int		i;
	int		count;
	bool	sq;
	bool	dq;

	i = 0;
	count = 0;
	sq = false;
	dq = false;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
		{
			sq = !sq;
			count++;
		}
		if (str[i] == '"' && !sq)
		{
			dq = !dq;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*remove_extra_quotes(char *new, char *temp, int i, int j)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	while (temp[i])
	{
		if (temp[i] == '\'' && !dq)
			sq = !sq;
		if (temp[i] == '"' && !sq)
			dq = !dq;
		else if (!(temp[i] == '\'' && !dq) && !(temp[i] == '"' && !sq))
		{
			new[j] = temp[i];
			j++;
		}
		i++;
	}
	return (new);
}

char	*token_word_remove_extra_quotes(char *new, t_data *data)
{
	char	*temp;
	int		remove_c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	remove_c = 0;
	temp = ft_strdup(new);
	free(new);
	new = NULL;
	remove_c = count_quotes(temp);
	new = ft_calloc(sizeof(char), ft_strlen(temp) - remove_c + 1);
	if (!new)
		error_exit(data, NULL, "Error alloc for new in token_word", 1);
	new = remove_extra_quotes(new, temp, i, j);
	free(temp);
	return (new);
}
