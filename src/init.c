/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 10:29:43 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/17 14:11:44 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function to initialize main struct.*/
void	init_main_struct(t_data *data)
{
	data->line = NULL;
	data->cmd_head = NULL;
	// data->cmd_current = NULL;
	// data->envp_head = NULL;
	
	// temp initialisation:
	data->cmd_current = malloc(sizeof(t_cmd));
	if (!data->cmd_current)
		ft_printf("malloc error\n");
	data->cmd_current->cmd = NULL;
	// data->cmd_current->here_doc = NULL;
	data->cmd_current->pipe = NULL;
	data->cmd_current->fd_in = 0;
	data->cmd_current->fd_out = 1;
}
