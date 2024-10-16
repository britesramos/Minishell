/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/11 13:34:56 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//temporary function until I have the cmd filled in data from Sara
void	exec(t_data *data)
{
	char	**args;
	
	int	i = 0;
	args = ft_split(data->line, ' ');
	if (ft_built_in_check(args, data) == 9)
	{
		i = 0;
		while (args[i])
		{
			free(args[i]);
			args[i] = NULL;
			i++;
		}
		free(args);
		return ; //TODO -> only if there are no other cmds
	}
	i = 0;
	ft_free(args);
	while (args[i])
	{
		ft_printf("to free arg[%d] %s\n", i, args[i]);
		free(args[i]);
		args[i] = NULL;
		i++;
		ft_printf("2. to free arg[%d] %s\n", i, args[i]);
	}
	free(args);
}
