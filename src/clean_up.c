/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:18:51 by sramos            #+#    #+#             */
/*   Updated: 2024/09/26 12:10:42 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_envp(t_envp *envp_head)
{
	t_envp	*current;
	t_envp	*next;

	current = envp_head;
	next = envp_head->next;
	while(current->next != NULL)
	{
		free(current->key);
		free(current->value);
		free(current);
		current = next;
		next = current->next;
	}
}

void	clean_up(t_data *data)
{
	free_envp(data->envp_head);
	free(data->line); /*This might have to be changed if readline is a loop, so it will alocate multiple times for line.*/
	free(data);
}