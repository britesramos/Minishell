/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/21 11:41:15 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

static char	*heredoc(t_data *data, char **heredoc_line, char *del, char **str)
{
	while (1)
	{
		ft_putstr_fd("> ", data->std[OUT]);
		*heredoc_line = get_next_line(data->std[IN]);
		if (*heredoc_line == NULL)
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
		*heredoc_line = expansion_heredoc(data, *heredoc_line);
		if (ft_strncmp(*heredoc_line, del, ft_strlen(del) + 1) == 0)
			break;
		*str = ft_strjoin(*str, *heredoc_line); //TODO add malloc check
		ft_free_string(*heredoc_line);
	}
	if (!(*str))
		return (NULL);
	return (*str);
}

t_token	*p_heredoc(t_token *current_token, t_cmd *c_cmd, t_data *data)
{
	char	*heredoc_line;
	char	*delimiter;
	char	*str;

	c_cmd->heredoc = true;
	current_token = current_token->next;
	delimiter = ft_strjoin(current_token->str, "\n");
	heredoc_line = NULL;
	str = NULL;
	ms_signals(HEREDOC);
	str = heredoc(data, &heredoc_line, delimiter, &str);
	if (str == NULL && data->exit_code == 128 + g_sign)
		return (NULL);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (str)
		ft_putstr_fd(str, c_cmd->fd_in);
	c_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	close(c_cmd->fd_in);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	ft_free_string(heredoc_line);
	ft_free_string(str);
	ft_free_string(delimiter);
	return (current_token);
}
