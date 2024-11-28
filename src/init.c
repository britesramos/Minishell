/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 10:29:43 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/28 11:35:24 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function to initialize main struct.*/
void	init_main_struct(t_data *data, char **envp)
{
	data->cmd_current = NULL;
	data->cmd_head = NULL;
	data->token_list = NULL;
	data->envp = envp;
	data->envp_head = NULL;
	data->exit_code = 0;
	data->line = NULL;
	data->nbr_pipes = 0;
	data->std[IN] = STDIN_FILENO;
	data->std[OUT] = STDOUT_FILENO;
	data->invalid_fd = false;
	data->hd_line = NULL;
}
