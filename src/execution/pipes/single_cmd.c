/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 07:41:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/14 14:56:05 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief dup2() for redirection, does nothing if in/out are STD IN/OUT.
/// From man dup2: If oldfd is a valid file descriptor, and newfd has the same
/// value as oldfd, then dup2() does nothing, and returns newfd.
static void	ft_dup_all(t_cmd *current, t_data *data)
{
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
		{
			perror("dup2 fd_in in single cmd");
			return ;
		}
		close_fd(&current->fd_in);
	}
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
		{
			perror("dup2 fd_out in single cmd");
			return ;
		}
		close_fd(&current->fd_out);
	}
}

static void	ft_single_child(t_data *data, char *path)
{
	if (access(data->cmd_current->cmd[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmd_current->cmd[0]);
	else
		path = get_path(data, data->cmd_current->cmd[0]);
	if (path != NULL)
	{
		data->exit_code = 0;
		execve(path, data->cmd_current->cmd, data->envp);
	}
	ft_putstr_fd(data->cmd_current->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	if (path != NULL)
	{
		free(path);
		path = NULL;
	}
	data->exit_code = 127;
	exit (data->exit_code);
}

void	single_cmd(t_data *data)
{
	pid_t	pid;
	char	*path;

	path = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("error: child in single cmd");
		return ;
	}
	if (data->cmd_current->heredoc == false)
		ms_signals(CHILD);
	if (pid == 0)
	{
		ft_dup_all(data->cmd_current, data);
		ft_single_child(data, path);
	}
	if (data->cmd_current->heredoc == true)
		ms_signals(HEREDOCP);
	else
		ms_signals(PARENT);
	waitpid(pid, &data->exit_code, 0);
}
