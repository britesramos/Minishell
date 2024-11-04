/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 07:41:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/04 12:15:17 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief dup2() for redirection, does nothing if in/out are STD IN/OUT.
/// From man dup2: If oldfd is a valid file descriptor, and newfd has the same
/// value as oldfd, then dup2() does nothing, and returns newfd.
static void	ft_dup_all(t_cmd *current)
{
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in in single cmd");
			return ;
		}
	}
	close(current->fd_in);
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out in single cmd");
			return ;
		}
		close(current->fd_out);
	}
}

//TODO -> check if exit_code=127
static void	ft_single_child(t_data *data, char *path)
{
	ft_printf("path = %s\n", path);
	if (access(data->cmd_current->cmd[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmd_current->cmd[0]);
	else
		path = get_path(data, data->cmd_current->cmd[0]);
	if (path != NULL)
		data->exit_code = execve(path, data->cmd_current->cmd, data->envp);
	ft_putstr_fd(data->cmd_current->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	if (path)
		free(path);
	path = NULL;
}

void	single_cmd(t_data *data)
{
	pid_t	pid;
	char	*path;
	int		wstatus;

	path = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("error child in single cmd");
		return ;
	}
	if (pid == 0)
	{
		ft_dup_all(data->cmd_current);
		ft_single_child(data, path);
	}
	close(data->cmd_current->fd_out);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		ft_printf("child %i exited with status: %d\n", pid, WIFEXITED(wstatus));
}
