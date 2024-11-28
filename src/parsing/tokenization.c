/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenization.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 20:24:34 by anonymous     #+#    #+#                 */
/*   Updated: 2024/10/24 20:24:34 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	token_word(t_data *data, int start, t_token **token_list)
{
	int		len;
	char	*new;

	new = NULL;
	len = len_result(data, start);
	new = ft_substr(data->line, start, len);
	if (!new)
		error_exit(data, NULL, "New str does not exist!\n", 1);
	if ((ft_strchr(new, '"') || ft_strchr(new, '\'')) && start != 0)
		new = token_word_remove_extra_quotes(new, data);
	else if (!(ft_strchr(new, '"') || ft_strchr(new, '\'')))
		new = token_word_remove_extra_spaces(new, data);
	if (ft_strlen(new) == 0)
	{
		free(new);
		return (start + len);
	}
	create_list(data, token_list, new, T_WORD);
	free(new);
	len--;
	return (start + len);
}

static int	token_append(t_data *data, int i, t_token **token_list, char *str)
{
	create_list(data, token_list, str, T_APPEND);
	return (i + 1);
}

static int	token_heredoc(t_data *data, int i, t_token **token_list, char *str)
{
	create_list(data, token_list, str, T_HEREDOC);
	return (i + 1);
}

void	tokenization(t_data *data)
{
	int	i;

	i = 0;
	if (!data->line || !data->line[i])
		return ;
	while (data->line[i])
	{
		while (ms_isspace(data->line[i]))
			i++;
		if (data->line[i] == '>' && data->line[i + 1] == '>')
			i = token_append(data, i, &data->token_list, ">>");
		else if (data->line[i] == '<' && data->line[i + 1] == '<')
			i = token_heredoc(data, i, &data->token_list, "<<");
		else if (data->line[i] == '>' && data->line[i + 1])
			create_list(data, &data->token_list, ">", T_REOUT);
		else if (data->line[i] == '<' && data->line[i + 1])
			create_list(data, &data->token_list, "<", T_REIN);
		else if (data->line[i] == '|')
			create_list(data, &data->token_list, "|", T_PIPE);
		else if (ms_isword(data->line[i]))
			i = token_word(data, i, &data->token_list);
		if (data->line[i] && (data->line[i] != '"' || data->line[i] != '\''))
			i++;
	}
}
