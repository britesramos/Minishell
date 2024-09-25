/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:29:43 by sramos            #+#    #+#             */
/*   Updated: 2024/09/25 15:40:05 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Function to initialize main struct.*/
void	init_main_struct(t_data *data)
{
	data->line = NULL;
	data->cmd_head = NULL;
	data->cmd_current = NULL;
	// data->envp_head = NULL;
}
