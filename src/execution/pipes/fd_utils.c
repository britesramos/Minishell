/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 09:14:19 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/12 14:34:52 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void	close_fd(int *fd)
{
	// printf("to close : %d\n", *fd);
	if (*fd > 2)
	{
		close(*fd);
		*fd = -3;
	}
}

static int	fds_first_cmd(t_cmd *current, t_ex *ex, t_data *data)
{
	/*in case of redirection in*/
	printf("will close READ in 1st cmd: %d\n", ex->p_fd[READ]);
	close_fd(&ex->p_fd[READ]);
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
			return (perror("error dup2() 1st cmd fd_in"), EXIT_FAILURE);
		printf("will close fd_in in the 1st cmd: %d\n", current->fd_in);
		close_fd(&current->fd_in);
	}
	/*in case of redirection out*/
	if (current->fd_out != data->std[OUT])
	{		
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd fd_out"), EXIT_FAILURE);
		printf("will close fd_out in the 1st cmd: %d\n", current->fd_out);
		close_fd(&current->fd_out);
	}
	else /*pipes*/
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd pipe_out"), EXIT_FAILURE);
	}
	printf("will close WRITE in 1st cmd :%d\n", ex->p_fd[WRITE]);
	close_fd(&ex->p_fd[WRITE]);
	return (EXIT_SUCCESS);
}

/// @brief the fd_in will always be either the p_fd[OUT] from the previous cmd or
//			redirection
static int	fds_in_between_cmd(t_cmd *current, t_ex *ex,t_data *data)
{
	/*it will be always either p_fd[OUT] or the redirection file*/
	if (current->fd_in == data->std[IN])
		current->fd_in = ex->fd_in;
	if (dup2(current->fd_in, data->std[IN]) == -1)
		return (perror("error dup2() cmd fd_in"), EXIT_FAILURE);
	printf("will close READ in [%d] cmd :%d\n", ex->i, ex->p_fd[READ]);
	close_fd(&ex->p_fd[READ]);
	printf("will close fd_in [%d] cmd :%d\n", ex->i, current->fd_in);
	close_fd(&current->fd_in);
	/*in case of the redirection*/
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() cmd fd_out"), EXIT_FAILURE);
		printf("will close fd_out [%d] cmd :%d\n", ex->i, current->fd_out);
		close_fd(&current->fd_out);
	}
	else /*pipes*/
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() cmd pipe_out"), EXIT_FAILURE);
	}
	printf("will close WRITE in [%d] cmd :%d\n", ex->i, ex->p_fd[WRITE]);
	close_fd(&ex->p_fd[WRITE]);
	return (EXIT_SUCCESS);
}

static int	fds_last_cmd(t_cmd *current, t_data *data, t_ex *ex)
{
	if (current->fd_in == data->std[IN])
		current->fd_in = ex->fd_in;
	// if (current->fd_in != data->std[IN])
	// {
	if (dup2(current->fd_in, data->std[IN]) == -1)
		return (perror("error dup2() last cmd fd_in"), EXIT_FAILURE);
	printf("will close fd_in the last cmd :%d\n", current->fd_in);
	close_fd(&current->fd_in);
	// }
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() last cmd fd_out"), EXIT_FAILURE);
		printf("will close fd_out the last cmd :%d\n", current->fd_out);
		close_fd(&current->fd_out);
	}
	return (EXIT_SUCCESS);
}

void	child_fd_handling(t_data *data, t_ex *ex)
{
	if (ex->i == 0)
		fds_first_cmd(data->cmd_current, ex, data);
	else if (ex->i == data->nbr_pipes)
		fds_last_cmd(data->cmd_current, data, ex);
	else
		fds_in_between_cmd(data->cmd_current, ex, data);
}