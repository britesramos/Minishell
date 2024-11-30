/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 14:19:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/30 15:52:48 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

static int	hd_signal(t_data *data, char **str, char *del_str)
{
	char	*tmp;
	char	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	if (data->hd_line == NULL)
	{
		if (g_sign == SIGINT)
		{
			data->exit_code = 128 + g_sign;
			ft_free_string(str);
			return (1);
		}
		tmp = ft_strjoin("end-of-file (wanted `", del_str);
		tmp1 = ft_strjoin("warning: here-document delimited by ", tmp);
		if (!tmp || !tmp1)
			error_exit(data, NULL, "malloc in hd_signal", -10);
		mini_error(tmp1, "')", data);
		ft_free_string(&tmp);
		data->exit_code = 0;
		return (2);
	}
	return (0);
}

static char	*get_tmp(t_data *data, char **str)
{
	char	*tmp;

	tmp = ft_strjoin(*str, data->hd_line);
	if (!tmp)
	{
		ft_free_string(str);
		error_exit(data, NULL, "malloc in heredoc", -10);
	}
	ft_free_string(str);
	ft_free_string(&data->hd_line);
	return (tmp);
}

static char	*heredoc(t_data *data, char *del, char **str, char *del_str)
{
	char	*tmp;
	int		check;

	while (1)
	{
		ft_putstr_fd("> ", data->std[OUT]);
		data->hd_line = get_next_line(data->std[IN]);
		check = hd_signal(data, str, del_str);
		if (check == 1)
			return (NULL);
		else if (check == 2)
			break ;
		data->hd_line = expansion_heredoc(data);
		if (ft_strncmp(data->hd_line, del, ft_strlen(del) + 1) == 0)
			break ;
		tmp = get_tmp(data, str);
		// tmp = ft_strjoin(*str, data->hd_line);
		// if (!tmp)
		// {
		// 	ft_free_string(str);
		// 	error_exit(data, NULL, "malloc in heredoc", -10);
		// }
		// ft_free_string(str);
		// ft_free_string(&data->hd_line);
		*str = tmp;
	}
	if (data->hd_line)
		ft_free_string(&data->hd_line);
	if (!(*str))
		return (NULL);
	return (*str);
}

static void	str_to_infile(t_data *data, char **str, t_cmd *c_cmd)
{
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	if (*str)
		ft_putstr_fd(*str, c_cmd->fd_in);
	ft_free_string(str);
	c_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	if (!c_cmd->infile)
		error_exit(data, NULL, "malloc in p_heredoc", -10);
	close(c_cmd->fd_in);
	c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	ft_free_string(&data->hd_line);
}

t_token	*p_heredoc(t_token *current_token, t_cmd *c_cmd, t_data *data)
{
	char	*delimiter;
	char	*str;

	c_cmd->heredoc = true;
	current_token = current_token->next;
	delimiter = ft_strjoin(current_token->str, "\n");
	if (!delimiter)
		error_exit(data, NULL, "malloc in p_heredoc", -10);
	str = NULL;
	ms_signals(HEREDOC);
	str = heredoc(data, delimiter, &str, current_token->str);
	ft_free_string(&delimiter);
	if (str == NULL && data->exit_code == 128 + g_sign)
	{
		ft_free_string(&str);
		return (NULL);
	}
	str_to_infile(data, &str, c_cmd);
	// c_cmd->fd_in = open("/tmp/heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0660);
	// if (str)
	// 	ft_putstr_fd(str, c_cmd->fd_in);
	// ft_free_string(&str);
	// c_cmd->infile = ft_strdup("/tmp/heredoc.txt");
	// if (!c_cmd->infile)
	// 	error_exit(data, NULL, "malloc in p_heredoc", -10);
	// close(c_cmd->fd_in);
	// c_cmd->fd_in = open("/tmp/heredoc.txt", O_RDWR, 0660);
	// ft_free_string(&data->hd_line);
	return (current_token);
}
