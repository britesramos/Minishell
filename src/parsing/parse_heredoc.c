/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/14 14:32:15 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*parse_heredoc(t_token *current_token, t_cmd *c_cmd, t_data *data)
{
	char	*heredoc_line;
	char	*delimiter;

	c_cmd->heredoc = true;
	current_token = current_token->next;
	delimiter = current_token->str;
	heredoc_line = NULL;
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (c_cmd->fd_in == -1)
		error_exit(data, NULL, "Error on opening heredoc temp file.\n", 2);
	while (1)
	{
		if (heredoc_line)
		{
			ft_putchar_fd('\n', c_cmd->fd_in);
			free(heredoc_line);
		}
		ms_signals(HEREDOCC);
		heredoc_line = readline("> ");
		if (heredoc_line == NULL)
		{
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putendl_fd("delimited by end-of-file (wanted `EOF')", 2);
			data->exit_code = 0;
			free (heredoc_line);
			return (current_token);
		}
		if (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		ft_putstr_fd(heredoc_line, c_cmd->fd_in);
	}
	c_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	close(c_cmd->fd_in);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	return (current_token);
}
