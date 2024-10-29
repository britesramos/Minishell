/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 07:41:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 12:49:58 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief dup2() for redirection, does nothing if in/out are STD IN/OUT.
/// From man dup2: If oldfd is a valid file descriptor, and newfd has the same
/// value as oldfd, then dup2() does nothing, and returns newfd.
static void	ft_dup_all(t_cmd *current)
{
	if (dup2(current->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 fd_in in single cmd");
		return ;
	}
	if (dup2(current->fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out in single cmd");
		return ;
	}
	close(current->fd_in);
	close(current->fd_out);
}

void	single_cmd(t_data *data, t_cmd *current, char **cmd)
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
		ft_dup_all(current);
		if (access(cmd[0], F_OK | X_OK) == 0)
			path = ft_strdup(cmd[0]);
		else
			path = get_path(data, cmd[0]);
		if (path != NULL)
			data->exit_code = execve(path, &cmd[0], data->envp);
		ft_putstr_fd(cmd[0], STDERR_FILENO); //TODO -> check if exit_code=127
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		if (path)
			free(path);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
	}
}
