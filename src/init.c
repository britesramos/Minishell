/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 10:29:43 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/22 10:58:44 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function to initialize main struct.*/
void	init_main_struct(t_data *data, char **envp)
{
	data->line = NULL;
	data->cmd_head = NULL;
	// data->cmd_current = NULL;
	data->envp_head = NULL;
	
	// temp initialisation:
	data->cmd_current = malloc(sizeof(t_cmd));
	if (!data->cmd_current)
		ft_printf("malloc error\n");
	data->cmd_current->cmd = NULL;
	data->cmd_current->here_doc = NULL;
	data->cmd_current->pipe = NULL;
	data->cmd_current->fd_in = STDIN_FILENO;
	data->cmd_current->fd_out = STDOUT_FILENO;
	data->kids = 0;
	data->exit_code = 0;
	data->envp = envp;
}
