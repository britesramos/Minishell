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

	len = 0;
	new = NULL;
	sq = false;
	dq = false;
	if (start == 0)
	{
		while (ms_isword(data->line[start + len]) && !ms_isspace(data->line[start + len]))
			len++;
	}
	else
	{
		if ((data->line[start] == '\'' || data->line[start] == '"') && data->line[start + 1] == '\0')
			return (start + 1);
		else
		{
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
		}
	}
	new = ft_substr(data->line, start, len);
	if (!new)
		error_exit(data, NULL, "New str does not exist!\n", 1);
	if (ft_strchr(new, '"') || ft_strchr(new, '\''))
		new = token_word_remove_extra_quotes(new, data);
	else if (!(ft_strchr(new, '"') || ft_strchr(new, '\'')))
		new = token_word_remove_extra_spaces(new, data);
	if (ft_strlen(new) == 0)
	{
		free(new);
		return (start + len);
	}
	create_t_list(data, token_list, new, T_WORD);
	free(new);
	len--;
	return (start + len);
}

static int	token_append(t_data *data, int i, t_token **token_list, char *str)
{
	create_t_list(data, token_list, str, T_APPEND);
	return (i + 1);
}

static int	token_heredoc(t_data *data, int i, t_token **token_list, char *str)
{
	create_t_list(data, token_list, str, T_HEREDOC);
	return (i + 1);
}

t_token	*tokenization(t_data *data, t_token *token_list)
{
	int	i;

	i = 0;
	if (!data->line || !data->line[i])
		return (NULL);
	while (data->line[i])
	{
		while (ms_isspace(data->line[i]))
			i++;
		if (data->line[i] == '>' && data->line[i + 1] == '>')
			i = token_append(data, i, &token_list, ">>");
		else if (data->line[i] == '<' && data->line[i + 1] == '<')
			i = token_heredoc(data, i, &token_list, "<<");
		else if (data->line[i] == '>' && data->line[i + 1])
			create_t_list(data, &token_list, ">", T_REOUT);
		else if (data->line[i] == '<' && data->line[i + 1])
			create_t_list(data, &token_list, "<", T_REIN);
		else if (data->line[i] == '|')
			create_t_list(data, &token_list, "|", T_PIPE);
		else if (ms_isword(data->line[i]))
			i = token_word(data, i, &token_list);
		if (data->line[i] && (data->line[i] != '"' || data->line[i] != '\''))
			i++;
	}
	return (token_list);
}
