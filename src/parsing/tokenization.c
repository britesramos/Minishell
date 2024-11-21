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
	while (ms_isword(data->line[start + len])
		&& !ms_isspace(data->line[start + len]))
		len++;
	new = ft_substr(data->line, start, len);
	if (!new)
		error_exit(data, NULL, "New str does not exist!\n", 1);
	if (ft_strchr(new, '"') || ft_strchr(new, '\''))
		new = token_word_remove_extra_quotes(new, data);
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
		if (data->line[i])
			i++;
	}
	return (token_list);
}
