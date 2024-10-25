/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/25 18:09:35 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_data *data, char **envp)
{
	t_token	*token_list;

	while (1)
	{
		token_list = NULL;
		if (data->line)
			free(data->line);
		data->line = NULL;
		data->line = readline("minishell:~$ ");
		if(data->line[0])
			add_history(data->line);
		if (input_checker(data) == 0)
		{
			token_list = tokenization(data, token_list); /*I think tokenization is basically done. Just need to make sure it accepts all types of words.*/

			t_token *current = token_list;
			while (current)
			{
				printf("%i\n", current->lenght);
				printf("%s\n", current->str);
				printf("%i\n\n\n", current->type);
				current = current->next;
			}
			free_token_list(token_list);
			// parse_input(data);
		}

	}
	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c 
}
