/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/05 17:33:30 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*parse_heredoc(t_token *current_token, t_cmd *current_cmd, t_data *data)
{
	char *heredoc_line;
	char *delimiter;

	current_token = current_token->next;
	delimiter = current_token->str;
	while (heredoc_line != delimiter)
	{
		if (heredoc_line)
			free(heredoc_line);
		heredoc_line = readline("> ");
		
		//Use a pipe OR:

		//Store it in a tempfile.
		//Make that file the Redirection Standard input file.
	}
}