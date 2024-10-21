/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/21 10:36:24 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//temporary function until I have the cmd filled in data from Sara
void	exec(t_data *data)
{
	char	**cmds;
	
	int	i = 0;
	cmds = ft_split(data->line, ' ');
	if (ft_builtin_manager(cmds, data) == 9)
	{
		i = 0;
		while (cmds[i])
		{
			free(cmds[i]);
			cmds[i] = NULL;
			i++;
		}
		free(cmds);
		return ; //TODO -> only if there are no other cmds
	}
	i = 0;
	// ft_free(cmds);
	while (cmds[i])
	{
		// ft_printf("to free cmd[%d] %s\n", i, cmds[i]);
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
		// ft_printf("2. to free cmd[%d] %s\n", i, cmds[i]);
	}
	free(cmds);
}
