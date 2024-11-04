/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/03 16:06:36 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	child_fd_handling(t_data *data, t_ex *ex)
{
	if (ex->i == 0)
	{
		fds_first_cmd(data->cmd_current, ex);
	}
	if (ex->i != 0 && ex->i != data->nbr_pipes)
	{
		fds_in_between_cmd(data->cmd_current, ex);
	}
	else if (ex->i == data->nbr_pipes && data->cmd_current->pipe == NULL)
	{
		fds_last_cmd(data->cmd_current, ex);
	}
}

static	int	ft_child(t_data *data, t_ex *ex)
{
	char	*path;

	child_fd_handling(data, ex);
	if (access(data->cmd_current->cmd[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmd_current->cmd[0]);
	else
		path = get_path(data, data->cmd_current->cmd[0]);
	if (path != NULL)
		data->exit_code = execve(path, &data->cmd_current->cmd[0], data->envp);
	ft_putstr_fd(data->cmd_current->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	if (path)
		free(path);
	path = NULL;
	return (EXIT_FAILURE);
}

static int	ft_parent(t_data *data, t_ex *ex)
{
	if (data || ex)
		ft_printf("hello\n");
	return (EXIT_SUCCESS);
}

static int	do_pipex(t_data *data, t_ex *ex)
{
	if (pipe(ex->p_fd) == -1)
		return (perror("error: pipe"), EXIT_FAILURE);
	ex->pid = fork();
	if (ex->pid == -1)
		return (perror("error: child"), EXIT_FAILURE);
	if (ex->pid == 0)
		ft_child(data, ex);
	else
		ft_parent(data, ex);
	return (EXIT_SUCCESS);
}

// check if the cmd is first middle last
// based on that, perform the fd's assignment
// run the cmd (should be the single one)
int	mltpl_cmd(t_data *data)
{
	t_ex	ex;

	ex.i = 0;
	while (data->cmd_current != NULL)
	{
		if (do_pipex(data, &ex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ex.i++;
		data->cmd_current = data->cmd_current->pipe;
	}
	return (EXIT_SUCCESS);
}
