/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 07:41:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/25 07:54:47 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief dup2() for redirection, does nothing if in/out are STD IN/OUT.
/// From man dup2: If oldfd is a valid file descriptor, and newfd has the same
/// value as oldfd, then dup2() does nothing, and returns newfd.
static int	ft_dup_all(t_cmd *current, t_data *data)
{
	if (current->fd_in == -1 || current->fd_out == -1)
		return (EXIT_FAILURE);
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
		{
			perror("dup2 fd_in in single cmd");
			return (EXIT_FAILURE);
		}
		close_fd(&current->fd_in);
	}
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
		{
			perror("dup2 fd_out in single cmd");
			return (EXIT_FAILURE);
		}
		close_fd(&current->fd_out);
	}
	return (EXIT_SUCCESS);
}

static void	ft_single_child(t_data *data)
{
	char	*path;

	path = NULL;
	get_path_error(data, &path);
	if (path != NULL)
		data->exit_code = execve(path, data->cmd_current->cmd, data->envp);
	int	error = errno;
	printf("in cmd error: %d\n", error);
	if (ft_strncmp(data->cmd_current->cmd[0], "0", 2) == 0)
		ft_putnbr_fd(127, STDERR_FILENO);
	else
		ft_putstr_fd(data->cmd_current->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	clean_up(data);
	ft_free_string(&path);
	exit (127);
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
	if (pid == 0)
	{
		if (ft_dup_all(data->cmd_current, data) == EXIT_FAILURE)
		{
			clean_up(data);
			exit (EXIT_FAILURE);
		}
		ft_single_child(data);
	}
	ms_signals(NONINTERACTIVE);
	waitpid(pid, &data->exit_code, 0);
	if (WIFSIGNALED(data->exit_code))
		data->exit_code = WTERMSIG(data->exit_code) + 128;
	else if (WIFEXITED(data->exit_code))
		data->exit_code = WEXITSTATUS(data->exit_code);
}
