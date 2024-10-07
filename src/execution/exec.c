/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/07 08:05:49 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec(t_data *data)
{
	char	**args;
	
	args = ft_split(data->line, ' ');
	ft_t_check(args, data->envp_head);
	int i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
