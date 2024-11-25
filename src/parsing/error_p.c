/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 08:34:01 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_exit_system(t_data *data, char *str, int type)
{
	int	len;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	len = ft_strlen(str);
	perror(str);
	data->exit_code = type;
	return (0);
}

int	error_exit(t_data *data, char *file, char *str, int type)
{
	int	len;
	int	lenfile;

	len = ft_strlen(str);
	lenfile = 0;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (file)
	{
		lenfile = ft_strlen(file);
		write(STDERR_FILENO, file, lenfile);
	}
	write(STDERR_FILENO, str, len);
	data->exit_code = type;
	return (0);
}
