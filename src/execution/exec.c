/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/26 15:10:49 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	bi_check(t_data *data)
{
	int	check;

	check = ft_builtin_manager(data, data->cmd_current->fd_out);
	if (check == 9)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (9);
	}
	else if (check == 3)
		return (9);
	else if (check == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	exec(t_data *data)
{
	int	check;

	check = 0;
	if (data->nbr_pipes == 0)
	{
		if (data->cmd_current->cmd)
		{
			check = bi_check(data);
			if (check == 9)
				return (9);
			else if (check == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			else
				single_cmd(data);
		}
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