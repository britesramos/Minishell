/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:12:15 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/26 18:13:01 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	path_error(t_data *data, char *cmd, int flag)
{
	char	*tmp;
	char	*str;
	char	*msg;

	if (flag == NO_PATH)
		msg = ft_strdup(": No such file or directory\n");
	else if (flag == IS_DIR)
		msg = ft_strdup(": Is a directory\n");
	else if (flag == NO_PERM)
		msg = ft_strdup(": Permission denied\n");
	if (flag == NO_COMMAND)
	{
		if (data->end_error == NULL)
			data->end_error = ft_strjoin(cmd, ": command not found\n");
		else
		{
			tmp = ft_strjoin(data->end_error, cmd);
			ft_free_string(&data->end_error);
			data->end_error = ft_strjoin(tmp, ": command not found\n");
		}
	}
	else
	{
		tmp = ft_strjoin("minishell: ", cmd);
		if (data->end_error == NULL)
			data->end_error = ft_strjoin(tmp, msg);
		else
		{
			str = ft_strjoin(data->end_error, tmp);
			ft_free_string(&data->end_error);
			data->end_error = ft_strjoin(str, ": Is a directory\n");
		}
		data->exit_code = 126;
	}
	if (flag == NO_PATH || flag == NO_COMMAND)
		data->exit_code = 127;
	else if (flag == IS_DIR || flag == NO_PERM)
		data->exit_code = 126;
	ft_free_string(&msg);
	ft_free_string(&tmp);
	ft_free_string(&str);
	clean_up(data);
}
