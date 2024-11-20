/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/20 08:38:56 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

t_token	*parse_heredoc(t_token *current_token, t_cmd *c_cmd, t_data *data)
{
	char	*heredoc_line;
	char	*delimiter;
	char	*str;

	c_cmd->heredoc = true;
	current_token = current_token->next;
	delimiter = ft_strjoin(current_token->str, "\n"); //TODO add malloc check
	heredoc_line = NULL;
	str = NULL;
	ms_signals(HEREDOC);
	while (1)
	{
		ft_putchar_fd('>', data->std[OUT]);
		heredoc_line = get_next_line(data->std[IN]);
		if (heredoc_line == NULL)
		{
			if (g_sign == SIGINT)
			{
				data->exit_code = 128 + g_sign;
				return (NULL);
			}
			ft_putchar_fd('\n', data->std[OUT]);
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putendl_fd("delimited by end-of-file (wanted `EOF')", 2);
			data->exit_code = 0;
			break ;
		}
		if (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break;
		str = ft_strjoin(str, heredoc_line); //TODO add malloc check
		free (heredoc_line);
	}
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (str)
		ft_putstr_fd(str, c_cmd->fd_in);
	c_cmd->infile = ft_strdup("/tmp/heredoc.txt"); //TODO add malloc check
	close(c_cmd->fd_in);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	if (heredoc_line)
		free (heredoc_line);
	if (str)
		free (str);
	if (delimiter)
		free (delimiter);
	return (current_token);
}

