/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 17:58:54 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/18 17:59:40 by sramos        ########   odam.nl         */
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
