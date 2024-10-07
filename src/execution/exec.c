/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/07 09:25:24 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec(t_data *data)
{
	char	**args;
	
	int	i = 0;
	args = ft_split(data->line, ' ');
	ft_t_check(args, data);
	while (args[i++])
		ft_printf("args[%d]: %s\n", i, args[i]);
	i = 0;
	// ft_free(args);
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
