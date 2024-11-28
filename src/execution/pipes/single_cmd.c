/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 07:41:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/28 11:04:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief dup2() for redirection, does nothing if in/out are STD IN/OUT.
/// From man dup2: If oldfd is a valid file descriptor, and newfd has the same
/// value as oldfd, then dup2() does nothing, and returns newfd.
static void	ft_dup_all(t_cmd *current, t_data *data)
{
	if (data->cmd_current->error != NULL)
	{
		ft_putendl_fd(data->cmd_current->error, STDERR_FILENO);
		clean_up(data);
		exit (EXIT_FAILURE);
	}
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

static void	ft_single_child(t_data *data)
{
	char	*path;

	path = NULL;
	get_path_error(data, &path);
	ft_free_string(&data->cmd_current->error);
	if (path != NULL)
		data->exit_code = execve(path, data->cmd_current->cmd, data->envp);
	if (ft_strncmp(data->cmd_current->cmd[0], "0", 2) == 0)
		cmd_error("127", ": command not found");
	else
		cmd_error(data->cmd_current->cmd[0], ": command not found");
	clean_up(data);
	ft_free_string(&path);
	exit (127);
}

void	single_cmd(t_data *data)
{
	pid_t	pid;

	ms_signals(NONINTERACTIVE);
	pid = fork();
	if (pid == -1)
	{
		perror("error: child in single cmd");
		return ;
	}
	if (pid == 0)
	{
		ft_dup_all(data->cmd_current, data);
		ft_single_child(data);
	}
	waitpid(pid, &data->exit_code, 0);
	if (WIFSIGNALED(data->exit_code))
		data->exit_code = WTERMSIG(data->exit_code) + 128;
	else if (WIFEXITED(data->exit_code))
		data->exit_code = WEXITSTATUS(data->exit_code);
}
