/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:12:15 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 14:56:34 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_extra_error(char *str, char *cmd, char *str1, t_data *data)
{
	char	*error;
	char	*error1;

	error = ft_strjoin(str, cmd);
	if (!error)
		error_exit(data, NULL, "malloc 1 in cmd_extra_error", -10);
	error1 = ft_strjoin(error, str1);
	if (!error1)
		error_exit(data, NULL, "malloc 2 in cmd_extra_error", -10);
	ft_putendl_fd(error1, STDERR_FILENO);
	ft_free_string(&error);
	ft_free_string(&error1);
}

void	cmd_error(char *cmd, char *str, t_data *data)
{
	char	*tmp;

	tmp = ft_strjoin(cmd, str);
	if (!tmp)
		error_exit(data, NULL, "malloc in cmd_error", -10);
	ft_putendl_fd(tmp, STDERR_FILENO);
	ft_free_string(&tmp);
}

void	mini_error(char *cmd, char *str, t_data *data)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!tmp)
		error_exit(data, NULL, "malloc 1 in mini_error", -10);
	tmp1 = ft_strjoin(tmp, str);
	if (!tmp1)
		error_exit(data, NULL, "malloc 2 in mini_error", -10);
	ft_putendl_fd(tmp1, STDERR_FILENO);
	ft_free_string(&tmp);
	ft_free_string(&tmp1);
}

void	path_error(t_data *data, char *cmd, int flag)
{
	if (flag == NO_PATH)
		mini_error(cmd, ": No such file or directory", data);
	else if (flag == NO_COMMAND)
		cmd_error(cmd, ": command not found", data);
	else if (flag == IS_DIR)
		mini_error(cmd, ": Is a directory", data);
	else if (flag == NO_PERM)
		mini_error(cmd, ": Permission denied", data);
	clean_up(data);
	if (flag == NO_PATH || flag == NO_COMMAND)
		exit(127);
	else if (flag == IS_DIR || flag == NO_PERM)
		exit(126);
}
