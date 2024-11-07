/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/07 18:09:48 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*parse_heredoc(t_token *current_token, t_cmd *current_cmd, t_data *data)
{
	char *heredoc_line;
	char *delimiter;

	current_token = current_token->next;
	delimiter = current_token->str;
	heredoc_line = NULL;
	current_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (current_cmd->fd_in == -1)
		error_exit(data, NULL, "Error on opening heredoc temp file.\n", 1);
	while (1)
	{
		if (heredoc_line)
		{
			ft_putchar_fd('\n', current_cmd->fd_in);	
			free(heredoc_line);
		}
		heredoc_line = readline("> ");
		if (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		ft_putstr_fd(heredoc_line, current_cmd->fd_in);
	}
	current_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	close(current_cmd->fd_in); //
	current_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660); //
	return (current_token);
}
