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

/*Fix norminette*/
static int	token_word(t_data *data, int end, t_token **token_list)
{
	int	len;
	char *new;

	len = 0;
	new = NULL;
	if (data->line[end + len] != '"' && data->line[end + len] != '\'')
	{
		while(ms_isword(data->line[end + len]) && !ms_isspace(data->line[end + len]))
			len++;
	}
	else if (data->line[end] == '\'')
	{
		end++;
		while(data->line[end + len] != '\'')
			len++;
	}
	else if (data->line[end] == '"')
	{
		end++;
		while(data->line[end + len] != '"')
			len++;
	}
	new = ft_substr(data->line, end, len);
	if (!new)
		error_exit(data, NULL, "New str does not exist!\n", 1);
	else
	{
		create_token_list(data, token_list, new, T_WORD);
		free(new);
	}
	return (end + len);
}

static int	token_apppend_heredoc(t_data *data, int i, t_token **token_list, char *str, t_token_t type)
{
	create_token_list(data, token_list, str, type);
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
		while(ms_isspace(data->line[i]))
			i++;
		// printf("tOKENIZATION: data->line[%i]: %c\n", i, data->line[i]);
		if (data->line[i] == '>' && data->line[i + 1] == '>')
			i = token_apppend_heredoc(data, i, &token_list, ">>", T_APPEND);
		else if (data->line[i] == '<' && data->line[i + 1] == '<')
			i = token_apppend_heredoc(data, i, &token_list, "<<", T_HEREDOC);
		else if (data->line[i] == '>' && data->line[i + 1])
			create_token_list(data, &token_list, ">", T_REOUT);
		else if (data->line[i] == '<' && data->line[i + 1])
			create_token_list(data, &token_list, "<", T_REIN);
		else if (data->line[i] == '|')
			create_token_list(data, &token_list, "|", T_PIPE);
		else if (ms_isword(data->line[i]))
			i = token_word(data, i, &token_list);
		i++;
	}
	return (token_list);
}
