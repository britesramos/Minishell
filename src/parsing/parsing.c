/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/10 13:50:52 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmd_list(t_cmd *list)
{
	t_cmd	*next;

	while (list)
	{
		next = list->pipe;
		if (list->cmd)
			ft_free_array(list->cmd);
		if (list->infile)
			free_close_fd(list->infile, list->fd_in);
		if (list->outfile)
			free_close_fd(list->outfile, list->fd_out);
		// ft_printf("to free list = %p\n", list);
		free(list);
		list = NULL;
		list = next;
		// ft_printf("list = %p\n", list);
	}
	list = NULL;
}

void	parsing(t_data *data, char **envp)
{
	t_token	*token_list;
	
	data->line = NULL; //ft_bezero(data);
	token_list = NULL;

	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c
	while (1)
	{
		if (data->line)
			ft_free_string(data->line);
		data->line = readline("minishell:~$ ");
		// printf("data->line: %s\n", data->line);
		if (!data->line[0])
			continue;
		if (!data->line)
			error_exit(data, NULL, "exit\n", 0);
		else
		{
			if (data->line[0])
				add_history(data->line);
			// parse_envp(data, envp); //This is resulting in segfault.
			if (input_checker(data) == 0)
			{
				expansion(data);
				token_list = tokenization(data, token_list);
				
				/*----------------------------------TEMP----------------------------------------------*/
				// t_token *current = token_list;
				// while (current)
				// {
				// 	if (current->type == T_PIPE)
				// 		printf("\n");
				// 	printf("LEN: %i - TYPE: %i - STR: %s\n", current->lenght, current->type, current->str);
				// 	current = current->next;
				// }
				/*----------------------------------TEMP----------------------------------------------*/
				parse_input(data, token_list);
				data->cmd_current = data->cmd_head;
				printf("DATA->LINE: %s, %p\n", data->line, data->line);
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
				// close (data->cmd_head->fd_in);
				if (token_list)
				{
					free_token_list(token_list);
					token_list = NULL;
				}
				if (exec(data) == 9)
					return ;
				if (data->cmd_head)
				{
					free_cmd_list(data->cmd_head);
					data->cmd_head = NULL;
				}
				data->nbr_pipes = 0;
				data->std[IN] = STDIN_FILENO;
				data->std[OUT] = STDOUT_FILENO;
				// should stay (for the moment commented out - infinite loop)
				wait(NULL);
		}
		}
	}
}



//Bash Input: ">file"  - **Does nothing.** STDERROR = 0;
