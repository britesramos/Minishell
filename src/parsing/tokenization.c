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

static int	token_word(t_data *data, int end, t_token **token_list)
{
	int	len;
	char *new;

	len = 0;
	new = NULL;
	while(ft_isalnum(data->line[end]))
	{
		len++;
		end++;
	}
	new = ft_substr(data->line, end - len, len);
	create_token_list(data, token_list, new, T_WORD);
	return (end - 1);
}

void	tokenization(t_data *data, t_token *token_list)
{
	int	i;

	i = 0;
	while(data->line[i])
	{
		while(ms_isspace(data->line[i]))
			i++;
		if (data->line[i] == '>' && data->line[i + 1] == '>')
		{
			create_token_list(data, &token_list, ">>", T_APPEND);
			i++;
		}
		else if (data->line[i] == '<' && data->line[i + 1] == '<')
		{
			create_token_list(data, &token_list, "<<", T_HEREDOC);
			i++;
		}
		else if (data->line[i] == '>')
			create_token_list(data, &token_list, ">", T_REOUT);
		else if (data->line[i] == '<')
			create_token_list(data, &token_list, "<", T_REIN);
		else if (data->line[i] == '|')
			create_token_list(data, &token_list, "|", T_PIPE);
		else if (ft_isalnum(data->line[i]))
			i = token_word(data, i, &token_list);
		i++;
	}
}
