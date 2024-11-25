/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_me.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 14:16:28 by anonymous     #+#    #+#                 */
/*   Updated: 2024/11/24 14:16:28 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd_list(t_data *data)
{
	int		i;
	t_cmd	*currentll;

	i = 0;
	currentll = data->cmd_head;
	while (currentll != NULL)
	{
		if (currentll->cmd)
		{
			while (currentll->cmd[i])
			{
				printf("This is cmd[%i]: %s - %p\n", i,
					currentll->cmd[i], currentll->cmd[i]);
				i++;
			}
		}
		printf("This is fd_in: %i\n", currentll->fd_in);
		printf("This is fd_out: %i\n", currentll->fd_out);
		printf("This is infile: %s\n", currentll->infile);
		printf("This is outfile: %s\n", currentll->outfile);
		printf("Nbr pipes: %i\n\n\n", data->nbr_pipes);
		currentll = currentll->pipe;
	}
}

void	print_token_list(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == T_PIPE)
			printf("\n");
		printf("LEN: %i - TYPE: %i - STR: %s\n",
			current->lenght, current->type, current->str);
		current = current->next;
	}
}
