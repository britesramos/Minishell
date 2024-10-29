/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/29 18:23:41 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_exit_system(t_data *data, char *str, int type)
{
	int	len;

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
	if (file)
	{
		lenfile = ft_strlen(file);
		write(1, file, lenfile);
	}
	write(1, str, len);
	//TODO:Clean_up; //Memory leaks from parsing envp might come from here.
	data->exit_code = type;
	return (0);
}