/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:12:15 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/28 11:55:21 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cmd_error(char *cmd, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(cmd, str);
	ft_putendl_fd(tmp, STDERR_FILENO);
	ft_free_string(&tmp);
}

void	mini_error(char *cmd, char *str)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin("minishell: ", cmd);
	tmp1 = ft_strjoin(tmp, str);
	ft_putendl_fd(tmp1, STDERR_FILENO);
	ft_free_string(&tmp);
	ft_free_string(&tmp1);
}

void	path_error(t_data *data, char *cmd, int flag)
{
	if (flag == NO_PATH)
		mini_error(cmd, ": No such file or directory");
	else if (flag == NO_COMMAND)
		cmd_error(cmd, ": command not found");
	else if (flag == IS_DIR)
		mini_error(cmd, ": Is a directory");
	else if (flag == NO_PERM)
		mini_error(cmd, ": Permission denied");
	clean_up(data);
	if (flag == NO_PATH || flag == NO_COMMAND)
		exit(127);
	else if (flag == IS_DIR || flag == NO_PERM)
		exit(126);
}
