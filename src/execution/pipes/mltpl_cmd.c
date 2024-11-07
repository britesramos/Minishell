/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/07 11:54:56 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	child_fd_handling(t_data *data, t_ex *ex)
{
	if (ex->i == 0)
		fds_first_cmd(data->cmd_current, ex, data);
	else if (ex->i == data->nbr_pipes)
		fds_last_cmd(data->cmd_current, data);
	else
		fds_in_between_cmd(data->cmd_current, ex, data);
}

static	int	ft_child(t_data *data, t_ex *ex)
{
	char	*path;
	int		built_in_check;

	child_fd_handling(data, ex);
	built_in_check = ft_builtin_manager(data);
	if (built_in_check == 0 || built_in_check == 9)
	{
		if (ex->i != data->nbr_pipes)
		{
			close_fd(&ex->p_fd[READ]);
			close_fd(&ex->p_fd[WRITE]);
		}
		exit (data->exit_code);
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
	data->exit_code = 127;
	exit (data->exit_code);
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
	//before the last cmd
	if (ex->i < data->nbr_pipes)
	{
		if (data->cmd_current->pipe->fd_in == data->std[IN])
			data->cmd_current->pipe->fd_in = ex->p_fd[READ];
	}
	if (data->cmd_current->fd_in != data->std[IN])
		close_fd(&data->cmd_current->fd_in);
	close_fd(&ex->p_fd[WRITE]);
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
	// wait(&status);
	// if (i > 0)
	// {
	// 	wait()
	// 	i--;
	// }
	waitpid(ex.pid, &status, 0);
	return (EXIT_SUCCESS);
}


// ls -la > test1 | cat test1 | grep "a" | sort | tee test2
// cat test1 | grep "8" | wc -l > out | wc 
// cat test1 | grep "8" | sort | tee test2