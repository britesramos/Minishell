/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/25 06:58:08 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	children_wait(t_data *data, t_ex *ex)
{
	int	i;

	i = 0;
	while (i < ex->i)
	{
		waitpid(ex->pid_store[i], &ex->status, 0);
		if (WIFSIGNALED(ex->status))
			data->exit_code = WTERMSIG(ex->status) + 128;
		else if (WIFEXITED(ex->status))
			data->exit_code = WEXITSTATUS(ex->status);
		i++;
	}
}

static int	builtin_check(t_data *data, t_ex *ex)
{
	int	built_in_check;

	built_in_check = ft_builtin_manager(data, data->std[OUT]);
	if (built_in_check == 0 || built_in_check == 9)
	{
		if (ex->i != data->nbr_pipes)
		{
			close_fd(&ex->p_fd[READ]);
			close_fd(&ex->p_fd[WRITE]);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static	int	ft_child(t_data *data, t_ex *ex)
{
	char	*path;
	int		bi_check;

	child_fd_handling(data, ex);
	bi_check = builtin_check(data, ex);
	if (bi_check == EXIT_SUCCESS)
	{
		clean_up(data);
		exit (EXIT_SUCCESS);
	}
	path = NULL;
	get_path_error(data, &path);
	if (path != NULL)
		data->exit_code = execve(path, data->cmd_current->cmd, data->envp);
	if (ft_strncmp(data->cmd_current->cmd[0], "0", 2) == 0)
		ft_putnbr_fd(127, STDERR_FILENO);
	else
		ft_putstr_fd(data->cmd_current->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": Command not found", STDERR_FILENO);
	clean_up(data);
	if (path)
		ft_free_string(&path);
	exit (127);
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
	ms_signals(NONINTERACTIVE);
	if (ex->fd_in != data->std[IN])
		close_fd(&ex->fd_in);
	ex->fd_in = ex->p_fd[READ];
	ex->pid_store[ex->i] = ex->pid;
	if (data->cmd_current->fd_in != data->std[IN])
		close_fd(&data->cmd_current->fd_in);
	if (ex->i != data->nbr_pipes)
		close_fd(&ex->p_fd[WRITE]);
	signal(SIGUSR1, SIG_IGN);
	return (EXIT_SUCCESS);
}

// check if the cmd is first middle last
// based on that, perform the fd's assignment
// run the cmd (should be the single one)
int	mltpl_cmd(t_data *data)
{
	t_ex	ex;

	ft_bzero(&ex, sizeof(ex));
	ex.i = 0;
	ex.fd_in = data->std[IN];
	while (data->cmd_current != NULL)
	{
		if (do_pipex(data, &ex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ex.i++;
		data->cmd_current = data->cmd_current->pipe;
	}
	ms_signals(NONINTERACTIVE);
	children_wait(data, &ex);
	while (waitpid(-1, &ex.status, WNOHANG) > 0)
		;
	return (EXIT_SUCCESS);
}

// ls -la > test1 | cat test1 | grep "a" | sort | tee test2
// cat test1 | grep "8" | sort | tee test2
// ls -la | grep 8 | wc -l
// cat | cat | ls
// echo Hello | mydog | wc -l
// cat >test1 | cat | ls
