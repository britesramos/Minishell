/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/25 00:20:28 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_exit(t_data *data, char *str, int type)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	//TODO:Clean_up; //Memory leaks from parsing envp might come from here.
	data->exit_code = type;
	return (0);
}