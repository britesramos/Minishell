/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 17:58:54 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/19 11:38:55 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_close_fd(char *file, int fd)
{
	if (file)
	{
		free(file);
		file = NULL;
	}
	close_fd(&fd);
}

void	free_null_2d_array(char **str)
{
	free(str);
	str = NULL;
}

void	free_null_array(char *str)
{
	free(str);
	str = NULL;
}
