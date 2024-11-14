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

static int	next_quote_mark(char *str, char c, int end)
{
	int	len;

	len = 0;
	end++;
	while (str[end] != c)
	{
		end++;
		len++;
	}
	return (len);
}

static int	token_word(t_data *data, int end, t_token **token_list)
{
	int		len;
	char	*new;

	len = 0;
	new = NULL;
	if (data->line[end + len] != '"' && data->line[end + len] != '\'')
	{
		while (ms_isword(data->line[end + len])
			&& !ms_isspace(data->line[end + len]))
			len++;
	}
	else if (data->line[end] == '\'' || data->line[end] == '"')
	{
		len = next_quote_mark(data->line, data->line[end], end);
		end++;
	}
	new = ft_substr(data->line, end, len);
	if (!new)
		error_exit(data, NULL, "New str does not exist!\n", 1);
	else
	{
		create_t_list(data, token_list, new, T_WORD);
		free(new);
	}
	return (end + len);
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
		// printf("This is data->line[%i]: %c\n", i, data->line[i]);
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
		i++;
	}
	return (token_list);
}
