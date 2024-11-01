/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/01 18:45:15 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_cmd_list(t_cmd *list)
{
	int	i;
	t_cmd *temp;

	temp = NULL;
	while(list)
	{
		i = 0;
		temp = list;
		if (temp->cmd)
		{
			while(temp->cmd[i])
			{
				free(temp->cmd[i]);
				temp->cmd[i] = NULL;
				// free_null((void**)&temp->cmd[i]);
				i++;
			}
			free(temp->cmd);
			temp->cmd = NULL;
			// free_null((void**)&temp->cmd);
		}
		if (temp->infile)
			free_close_fd(temp->infile, temp->fd_in);
		if (temp->outfile)
			free_close_fd(temp->outfile, temp->fd_out);
		list = list->pipe;
		list = NULL;
		free(temp);
		temp = NULL;
		// free_null((void**)&temp);
	}
}

void	parsing(t_data *data, char **envp)
{
	envp = NULL;
	t_token	*token_list;
	data->line = NULL; //ft_bezero(data);
	token_list = NULL;

	while (1)
	{
		if (data->line)
			free(data->line);
		data->line = readline("minishell:~$ ");
		if (!data->line)
			error_exit(data, NULL, "exit\n", 0); 
		if (data->line[0])
			add_history(data->line);
		if (input_checker(data) == 0)
		{
			token_list = tokenization(data, token_list); /*I think tokenization is basically done. Just need to make sure it accepts all types of words.*/
			
			/*----------------------------------TEMP----------------------------------------------*/
			// t_token *current = token_list;
			// while (current)
			// {
			// 	printf("%i\n", current->lenght);
			// 	printf("%s\n", current->str);
			// 	printf("%i\n\n\n", current->type);
			// 	current = current->next;
			// }
			/*----------------------------------TEMP----------------------------------------------*/

			parse_input(data, token_list);

			/*----------------------------------TEMP----------------------------------------------*/
			t_cmd *currentll = data->cmd_head;
			while (currentll != NULL)
			{
				int i = 0;
				if (currentll->cmd)
				{
					while(currentll->cmd[i])
					{
						printf("This is cmd[%i]: %s - %p\n", i, currentll->cmd[i], currentll->cmd[i]);
						i++;
					}
				}
				printf("This is fd_in: %i\n", currentll->fd_in);
				printf("This is fd_out: %i\n", currentll->fd_out);
				printf("This is infile: %s\n", currentll->infile);
				printf("This is outfile: %s\n\n\n", currentll->outfile);
				printf("Nbr pipes: %i\n", data->nbr_pipes);
				currentll = currentll->pipe;
			}
			/*----------------------------------TEMP----------------------------------------------*/

			if (token_list)
			{
				free_token_list(token_list);
				token_list = NULL;
			}
			// exec(data);
			if (data->cmd_head)
			{
				free_cmd_list(data->cmd_head);
				data->cmd_head = NULL;
			}
			if (data->cmd_head == NULL)
				printf("data->cmd_head does not exist!\n");
			data->nbr_pipes = 0;
		}
	}
	// parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c 
}



//Bash Input: ">file"  - **Does nothing.** STDERROR = 0;
