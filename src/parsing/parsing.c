/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/29 19:30:16 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_cmd_list(t_cmd *list)
{
	int	i;

	i = 0;
	while(list)
	{
		if (list->cmd)
		{
			while(list->cmd[i])
			{
				free(list->cmd[i]);
				list->cmd[i] = NULL;
				i++;
			}
		}
		if (list->infile)
			free_close_fd(list->infile, list->fd_in);
		if (list->outfile)
			free_close_fd(list->outfile, list->fd_out);
		list->append = false;
		free (list->cmd);
		free (list);
		list = list->pipe;
	}
}

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
		if (data->line[0])
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


			parse_input(data, token_list);

			
			t_cmd *currentll = data->cmd_head;
			while (currentll != NULL)
			{
				int i = 0;
				if (currentll->cmd) //there is a problem with the ll header. I is only saving the last node as the head.
				{
					while(currentll->cmd[i])
					{
						printf("This is cmd[%i]: %s\n", i, currentll->cmd[i]);
						i++;
					}
				}
				printf("This is fd_in: %i\n", currentll->fd_in);
				printf("This is fd_out: %i\n", currentll->fd_out);
				printf("This is infile: %s\n", currentll->infile);
				printf("This is outfile: %s\n", currentll->outfile);
				currentll = currentll->pipe;
			}



			free_token_list(token_list);
			// free(data->line);
			// exec(data);
			free_cmd_list(data->cmd_head);
		}
	}
	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c 
}
