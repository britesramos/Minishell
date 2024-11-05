/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 09:14:19 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/05 11:06:26 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void	close_fd(int fd)
{
	close (fd);
	fd = -3;
}

int	fds_first_cmd(t_cmd *current, t_ex *ex, t_data *data)
{
	close_fd (ex->p_fd[READ]);
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
			return (perror("error dup2() 1st cmd fd_in"), EXIT_FAILURE);
		close_fd (current->fd_in);
	}
	
	if (current->fd_out != data->std[OUT])
	{
		close_fd (ex->p_fd[WRITE]);
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd fd_out"), EXIT_FAILURE);
		close_fd (current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd pipe_out"), EXIT_FAILURE);
		close_fd(ex->p_fd[WRITE]);
	}
	return (EXIT_SUCCESS);
}

/// @brief the fd_in will always be either the p_fd[OUT] from the previous cmd or
//			redirection
/// @param current 
/// @param ex 
/// @param data 
/// @return 
int	fds_in_between_cmd(t_cmd *current, t_ex *ex,t_data *data)
{
	if (dup2(current->fd_in, data->std[IN]) == -1)
		return (perror("error dup2() cmd fd_in"), EXIT_FAILURE);
	close_fd(current->fd_in);
	if (current->fd_out != data->std[OUT])
	{
		close_fd (ex->p_fd[WRITE]);
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() cmd fd_out"), EXIT_FAILURE);
		close_fd (current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() cmd pipe_out"), EXIT_FAILURE);
		close_fd(ex->p_fd[WRITE]);
	}
	return (EXIT_SUCCESS);
}

int	fds_last_cmd(t_cmd *current, t_data *data)
{
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
			return (perror("error dup2() last cmd fd_in"), EXIT_FAILURE);
		close_fd (current->fd_in);
	}
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() last cmd fd_out"), EXIT_FAILURE);
		close_fd (current->fd_out);
	}
	return (EXIT_SUCCESS);
}
