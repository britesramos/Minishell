/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/15 08:59:22 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec(t_data *data)
{
	int	check;

	if (data->nbr_pipes == 0)
	{
		// ms_signals(PARENT);
		check = ft_builtin_manager(data, data->cmd_current->fd_out);
		if (check == 9)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (9);
		}
		else if (check == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			single_cmd(data);
	}
	else
		mltpl_cmd(data);
	return (EXIT_SUCCESS);
}

/*
TESTING ON
cat | exit | cat | ls
cat | cat | cat ls
cat | exit | cat test | ls
ls -l >test | wc -l < test > test2 | pwd
*/