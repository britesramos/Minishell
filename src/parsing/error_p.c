/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 17:31:23 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_exit_clean_up(t_data *data)
{
	if (data->cmd_head)
		free_cmd_list(data->cmd_head);
	if (data->token_list)
	{
		free_token_list(data->token_list);
		data->token_list = NULL;
	}
}

int	error_exit_system(t_data *data, char *str, t_cmd *cmd, int type)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->error == NULL)
	{
		cmd->error = ft_strjoin(str, ": ");
		tmp = ft_strjoin("minishell: ", cmd->error);
		ft_free_string(&cmd->error);
		cmd->error = ft_strjoin(tmp, strerror(errno));
		ft_free_string(&tmp);
		ft_putstr_fd(cmd->error, STDERR_FILENO); //
	}
	data->exit_code = type;
	return (0);
}

int	error_exit(t_data *data, char *file, char *str, int type)
{
	int	len;
	int	lenfile;

	len = ft_strlen(str);
	lenfile = 0;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (file)
	{
		lenfile = ft_strlen(file);
		write(STDERR_FILENO, file, lenfile);
	}
	write(STDERR_FILENO, str, len);
	error_exit_clean_up(data);
	data->exit_code = type;
	return (0);
}
