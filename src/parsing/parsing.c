/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/25 00:28:16 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_token_list(t_token *token_list)
{
	while(token_list)
	{
		free (token_list);
		token_list = token_list->next;
	}
}

void	parsing(t_data *data, char **envp)
{
	t_token	*token_list;

	token_list = NULL;
	while (1)
	{
		if (data->line)
			free(data->line);
		data->line = NULL;
		data->line = readline("minishell:~$ ");
		if(data->line[0])
			add_history(data->line);
		if (input_checker(data) == 0)
		{
			tokenization(data, token_list);

			// parse_input(data);
		}
		/*Is the token_list existing?*/
			t_token *current = token_list;
			while (current)
			{
				printf("%i\n", current->lenght);
				printf("%s\n", current->str);
				printf("%i\n\n\n", current->type);
				current = current->next;
			}
	}
	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c 
	free_token_list(token_list);
}
