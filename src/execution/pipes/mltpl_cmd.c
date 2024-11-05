/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/05 11:02:25 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	child_fd_handling(t_data *data, t_ex *ex)
{
	if (ex->i == 0)
	{
		// ft_putendl_fd("in the first cmd:", data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_in, data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_out, data->std[OUT]);
		// ft_putnbr_fd(ex->p_fd[WRITE], data->std[OUT]);
		// ft_putnbr_fd(ex->p_fd[WRITE], data->std[OUT]);
		// ft_putendl_fd("end of the first cmd", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		fds_first_cmd(data->cmd_current, ex, data);
	}
	else if (ex->i == data->nbr_pipes)
	{
		// ft_putendl_fd("in the last cmd:", data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_in, data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_out, data->std[OUT]);
		// ft_putendl_fd("end of the last cmd", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		fds_last_cmd(data->cmd_current, data);
		
	}
	else
	{
		// ft_putendl_fd("in between cmd:", data->std[OUT]);
		// ft_putnbr_fd(ex->i, data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_in, data->std[OUT]);
		// ft_putnbr_fd(data->cmd_current->fd_out, data->std[OUT]);
		// ft_putnbr_fd(ex->p_fd[READ], data->std[OUT]);
		// ft_putnbr_fd(ex->p_fd[WRITE], data->std[OUT]);
		// ft_putendl_fd("end of in between cmd", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		// ft_putendl_fd(" ", data->std[OUT]);
		fds_in_between_cmd(data->cmd_current, ex, data);
	}
}

static	int	ft_child(t_data *data, t_ex *ex)
{
	char	*path;
	int		built_in_check;

	child_fd_handling(data, ex);
	built_in_check = ft_builtin_manager(data);
	if ( built_in_check == 0 || built_in_check == 9)
	{
		if (ex->i != data->nbr_pipes)
		{
			close_fd (ex->p_fd[READ]);
			close_fd (ex->p_fd[WRITE]);
		}
		return (EXIT_FAILURE);
	}
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

static int	do_pipex(t_data *data, t_ex *ex)
{
	if (ex->i != data->nbr_pipes && pipe(ex->p_fd) == -1)
		return (perror("error: pipe"), EXIT_FAILURE);
	ex->pid = fork();
	if (ex->pid == -1)
		return (perror("error: child"), EXIT_FAILURE);
	if (ex->pid == 0)
		ft_child(data, ex);
	if (ex->i != data->nbr_pipes)
	{
		if (data->cmd_current->pipe->fd_in == data->std[IN])
			data->cmd_current->pipe->fd_in = ex->p_fd[READ];
	}
	close_fd (data->cmd_current->fd_in);
	close_fd (ex->p_fd[WRITE]);
	return (EXIT_SUCCESS);
}

// check if the cmd is first middle last
// based on that, perform the fd's assignment
// run the cmd (should be the single one)
int	mltpl_cmd(t_data *data)
{
	t_ex	ex;
	int		status;

	ex.i = 0;
	while (data->cmd_current != NULL)
	{
		if (do_pipex(data, &ex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ex.i++;
		data->cmd_current = data->cmd_current->pipe;
	}
	wait(&status);
	return (EXIT_SUCCESS);
}
