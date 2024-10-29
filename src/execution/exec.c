/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 12:20:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec(t_data *data)
{
	int		i;
	char	**cmd;
	t_cmd	*current;

	i = 0;
	
	if (data->nbr_pipes == 0)
	{
		current = data->cmd_current;
		cmd = current->cmd;
		if (ft_builtin_manager(data, current) == 9)
			return (9);
		else
			single_cmd(data, current, cmd);
	}
	else 
		mltpl_cmd(data);
	return (0);
}

/*
TESTING ON
cat | exit | cat | ls
cat | cat | cat ls
cat | exit | cat test | ls
ls -l >test | wc -l < test > test2 | pwd
*/