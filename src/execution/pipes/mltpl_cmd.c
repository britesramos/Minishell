/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/08 12:01:06 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	children_wait(t_ex *ex)
{
	int	i;
	int	status;

	i = 0;
	while (i < ex->i)
	{
		waitpid(ex->pid_store[i], &status, 0);
		i++;
	}
	return (status);
}

static int	builtin_check(t_data *data)
{
	int	built_in_check;

	built_in_check = ft_builtin_manager(data);
	if (built_in_check == 0)
		return (EXIT_SUCCESS);
	// else if (built_in_check == 9)
	// 	return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static	int	ft_child(t_data *data, t_ex *ex)
{
	char	*path;
	int		bi_check;

	child_fd_handling(data, ex);
	bi_check = builtin_check(data);
	if (bi_check == EXIT_SUCCESS)
		exit (data->exit_code);
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
	ex->pid_store[ex->i] = ex->pid;
	/*close the file in case of the redirection*/
	if (data->cmd_current->fd_in != data->std[IN])
		close_fd(&data->cmd_current->fd_in);
	if (ex->i != 0)
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
	children_wait(&ex);
	waitpid(ex.pid, &status, 0);
	// wait(&status);
	return (EXIT_SUCCESS);
}


// ls -la > test1 | cat test1 | grep "a" | sort | tee test2
// cat test1 | grep "8" | sort | tee test2
// ls -la | grep 8 | wc -l