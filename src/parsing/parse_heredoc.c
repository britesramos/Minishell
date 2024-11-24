/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/24 20:24:11 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

static char	*heredoc(t_data *data, char **heredoc_line, char *del, char **str)
{
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("> ", data->std[OUT]);
		*heredoc_line = get_next_line(data->std[IN]);
		if (*heredoc_line == NULL)
		{
			if (g_sign == SIGINT)
			{
				data->exit_code = 128 + g_sign;
				ft_free_string(str);
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
			break ;
		tmp = ft_strjoin(*str, *heredoc_line);
		if (!tmp)
			error_exit(data, NULL, "Fail to alloc in heredoc\n", 1);
		ft_free_string(str);
		ft_free_string(heredoc_line);
		if (!(*tmp))
			return (NULL);
		*str = tmp;
	}
	if (*heredoc_line)
		ft_free_string(heredoc_line);
	if (!(*str))
		return (NULL);
	return (*str);
}

t_token	*p_heredoc(t_token *current_token, t_cmd *c_cmd, t_data *data)
{
	char	*delimiter;
	char	*str;

	c_cmd->heredoc = true;
	current_token = current_token->next;
	delimiter = ft_strjoin(current_token->str, "\n");
	data->hd_line = NULL;
	str = NULL;
	ms_signals(HEREDOC);
	str = heredoc(data, &data->hd_line, delimiter, &str);
	ft_free_string(&delimiter);
	if (str == NULL && data->exit_code == 128 + g_sign)
	{
		ft_free_string(&str);
		return (NULL);
	}
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (str)
		ft_putstr_fd(str, c_cmd->fd_in);
	ft_free_string(&str);
	c_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	close(c_cmd->fd_in);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	ft_free_string(&data->hd_line);
	return (current_token);
}
