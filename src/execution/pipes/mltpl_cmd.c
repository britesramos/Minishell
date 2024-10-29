/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mltpl_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:25:11 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 12:58:17 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


// check if the cmd is first middle last
// based on that, perform the fd's assignment
// run the cmd (should be the single one)
int	mltpl_cmd(t_data *data)
{
	if (data->cmd_current)
		ft_printf("hello\n");
	return (EXIT_SUCCESS);
	//check if it's a first or middle or last cmd
}