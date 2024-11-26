/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 10:59:31 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

static int	tmp_help(t_data *data, char **heredoc_line, char **str, char **tmp)
{
	if (!*tmp)
		error_exit(data, NULL, "Fail to alloc in heredoc\n", 1);
	ft_free_string(str);
	ft_free_string(heredoc_line);
	if (!(**tmp))
		return (1);
	return (0);
}

static int	hd_signal(t_data *data, char **heredoc_line, char **str)
{
	if (*heredoc_line == NULL)
	{
		if (g_sign == SIGINT)
		{
			printf("in hd_signal getting SIGINT\n");
			data->exit_code = 128 + g_sign;
			ft_free_string(str);
			return (1);
		}
		ft_putchar_fd('\n', data->std[OUT]);
		ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
		ft_putendl_fd("delimited by end-of-file (wanted `EOF')", 2);
		data->exit_code = 0;
		return (2);
	}
	return (0);
}

static char	*heredoc(t_data *data, char *del, char **str)
{
	char	*tmp;
	int		check;

	while (1)
	{
		ft_putstr_fd("> ", data->std[OUT]);
		data->hd_line = get_next_line(data->std[IN]);
		check = hd_signal(data, &data->hd_line, str);
		if (check == 1)
			return (NULL);
		else if (check == 2)
			break ;
		data->hd_line = expansion_heredoc(data);
		if (ft_strncmp(data->hd_line, del, ft_strlen(del) + 1) == 0)
			break ;
		tmp = ft_strjoin(*str, data->hd_line);
		if (tmp_help(data, &data->hd_line, str, &tmp) == 1)
			return (NULL);
		*str = tmp;
	}
	if (data->hd_line)
		ft_free_string(&data->hd_line);
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
	str = NULL;
	ms_signals(HEREDOC);
	str = heredoc(data, delimiter, &str);
	ft_free_string(&delimiter);
	if (str == NULL && data->exit_code == 128 + g_sign)
	{
		printf("data->exit_code = %d\n", data->exit_code);
		printf("did I get here after SIGINT?\n");
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
