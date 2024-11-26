/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 09:14:19 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/26 07:45:36 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	close_fd(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -3;
	}
}

/// @brief order of ifs:
//	in case of redirections in | 
//	in case of redirection out |
//	pipes
static int	fds_first_cmd(t_cmd *current, t_ex *ex, t_data *data)
{
	close_fd(&ex->p_fd[READ]);
	if (current->fd_in != data->std[IN])
	{
		if (dup2(current->fd_in, data->std[IN]) == -1)
			return (perror("error dup2() 1st cmd fd_in"), EXIT_FAILURE);
		close_fd(&current->fd_in);
	}
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd fd_out"), EXIT_FAILURE);
		close_fd(&current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() 1st cmd pipe_out"), EXIT_FAILURE);
	}
	close_fd(&ex->p_fd[WRITE]);
	return (EXIT_SUCCESS);
}

/// @brief the fd_in will always be either the p_fd[OUT] from the previous cmd
// 	or redirection |
// 	then, if in case of the redirection out | or pipes
static int	fds_in_between_cmd(t_cmd *current, t_ex *ex, t_data *data)
{
	if (current->fd_in == data->std[IN])
		current->fd_in = ex->fd_in;
	if (dup2(current->fd_in, data->std[IN]) == -1)
		return (perror("error dup2() cmd fd_in"), EXIT_FAILURE);
	close_fd(&ex->p_fd[READ]);
	close_fd(&current->fd_in);
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() cmd fd_out"), EXIT_FAILURE);
		close_fd(&current->fd_out);
	}
	else
	{
		if (dup2(ex->p_fd[WRITE], data->std[OUT]) == -1)
			return (perror("error dup2() cmd pipe_out"), EXIT_FAILURE);
	}
	close_fd(&ex->p_fd[WRITE]);
	return (EXIT_SUCCESS);
}

/// @brief fd_in will be always either redirection or pipes |
// 	fd_out will be dupped only in case of redirection
static int	fds_last_cmd(t_cmd *current, t_data *data, t_ex *ex)
{
	if (current->fd_in == data->std[IN])
		current->fd_in = ex->fd_in;
	if (dup2(current->fd_in, data->std[IN]) == -1)
		return (perror("error dup2() last cmd fd_in"), EXIT_FAILURE);
	close_fd(&current->fd_in);
	if (current->fd_out != data->std[OUT])
	{
		if (dup2(current->fd_out, data->std[OUT]) == -1)
			return (perror("error dup2() last cmd fd_out"), EXIT_FAILURE);
		close_fd(&current->fd_out);
	}
	return (EXIT_SUCCESS);
}

void	child_fd_handling(t_data *data, t_ex *ex)
{

	if (data->cmd_current->error != NULL)
	{
		ft_putendl_fd(data->cmd_current->error, STDERR_FILENO);
		close_fd(&ex->p_fd[READ]);
		close_fd(&ex->p_fd[WRITE]);
		clean_up(data);
		exit (EXIT_FAILURE);
	}
	if (ex->i == 0)
		fds_first_cmd(data->cmd_current, ex, data);
	else if (ex->i == data->nbr_pipes)
		fds_last_cmd(data->cmd_current, data, ex);
	else
		fds_in_between_cmd(data->cmd_current, ex, data);
}
