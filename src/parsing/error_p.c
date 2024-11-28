/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/28 11:59:42 by sramos        ########   odam.nl         */
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
	}
	data->exit_code = type;
	return (0);
}

int	error_exit(t_data *data, char *file, char *str, int type)
{
	int		len;
	int		lenfile;
	char	*tmp;
	char	*tmp1;

	len = ft_strlen(str);
	lenfile = 0;
	tmp = NULL;
	tmp1 = NULL;
	if (file)
	{
		tmp1 = ft_strjoin("minishell: ", file);
		tmp = ft_strjoin(tmp1, str);
		ft_free_string(&tmp1);
	}
	else
		tmp = ft_strjoin("minishell: ", str);
	ft_putendl_fd(tmp, STDERR_FILENO);
	ft_free_string(&tmp);
	error_exit_clean_up(data);
	data->exit_code = type;
	return (0);
}
