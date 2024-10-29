/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 09:14:19 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 09:14:46 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	fds_first_cmd(t_cmd *current, t_ex *ex)
{
	close (ex->p_fd[READ]);
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
			return (perror("error dup2() 1st cmd fd_in"), EXIT_FAILURE);
		close(current->fd_in);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		close(ex->p_fd[WRITE]);
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
			return (perror("error dup2() 1st cmd fd_out"), EXIT_FAILURE);
		close(current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], STDOUT_FILENO) == -1)
			return (perror("error dup2() 1st cmd pipe_out"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	fds_in_between_cmd(t_cmd *current, t_ex *ex)
{
	if (current->fd_in != STDIN_FILENO)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
			return (perror("error dup2() cmd fd_in"), EXIT_FAILURE);
		close(current->fd_in);
		close (ex->p_fd[READ]);
	}
	else
	{
		if (dup2(ex->p_fd[READ], STDIN_FILENO) == -1)
			return (perror("error dup2() cmd pipe_in"), EXIT_FAILURE);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		close (ex->p_fd[WRITE]);
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
			return (perror("error dup2() cmd fd_out"), EXIT_FAILURE);
		close(current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], STDOUT_FILENO) == -1)
			return (perror("error dup2() cmd pipe_out"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	fds_last_cmd(t_cmd *current, t_ex *ex)
{
	if (current->fd_in != STDIN_FILENO)
	{
		close(ex->p_fd[READ]);
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
			return (perror("error dup2() last cmd fd_in"), EXIT_FAILURE);
		close(current->fd_in);
	}
	else
	{
		if (dup2(ex->p_fd[READ], STDIN_FILENO) == -1)
			return (perror("error dup2() last cmd pipe_in"), EXIT_FAILURE);
		close(ex->p_fd[READ]);
	}
	if (current->fd_out != STDOUT_FILENO)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
			return (perror("error dup2() last cmd fd_out"), EXIT_FAILURE);
		close(current->fd_out);
	}
	close(ex->p_fd[WRITE]);
		return (EXIT_SUCCESS);
}