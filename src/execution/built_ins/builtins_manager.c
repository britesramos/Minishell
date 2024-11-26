/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_manager.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:05:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/26 08:34:49 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	exit_help(char **cmd, t_data *data)
{
	int status;

	status = ft_exit(cmd, data);
	if (status == 0)
		return (9);
	else if (status == 3)
		return (3);
	return (EXIT_SUCCESS);
}

static int	fd_check(t_data *data)
{
	if (data->cmd_current->error != NULL)
	{
		ft_putendl_fd(data->cmd_current->error, STDERR_FILENO);
		return (1);
	}
	return (0);
}

/// @brief checks if a cmd is a builtin, if not increments the number of kids
/// @return 0 when cmd=builtin, 9 when exit should work, 1 when cmd != builtin
int	ft_builtin_manager(t_data *data, int fd)
{
	char	**cmd;

	if (fd_check(data) == 1)
		return (EXIT_SUCCESS);
	cmd = data->cmd_current->cmd;
	if (!cmd)
		return (EXIT_FAILURE);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (ft_cd(cmd, data), 0);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (ft_echo(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (ft_env(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
			return (exit_help(cmd, data));
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (ft_export(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (ft_pwd(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (ft_unset(cmd, data), 0);
	return (EXIT_FAILURE);
}
