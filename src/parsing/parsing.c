/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosia <gosia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:18 by sramos            #+#    #+#             */
/*   Updated: 2024/11/21 21:02:24 by gosia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

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
		if (list->heredoc == true)
			unlink(list->infile);
		free(list);
		list = NULL;
		list = next;
	}
	list = NULL;
}

void	parsing(t_data *data, char **envp)
{
	t_token	*token_list;

	data->line = NULL;
	token_list = NULL;
	parse_envp(data, envp);
	while (1)
	{
		g_sign = 0;
		if (data->line)
			ft_free_string(data->line);
		ms_signals(INTERACTIVE);
		data->line = readline("minishell:~$ ");
		if (data->line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			data->exit_code = 0;
			return ;
		}
		if (!data->line[0])
			continue ;
		if (data->line[0])
			add_history(data->line);
		if (input_checker(data) == 0 && !only_spaces(data))
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
			if (parse_input(data, token_list) == 9)
			{
				if (token_list)
				{
					free_token_list(token_list);
					token_list = NULL;
				}
				if (data->cmd_head)
				{
					free_cmd_list(data->cmd_head);
					data->cmd_head = NULL;
				}
				data->nbr_pipes = 0;
				data->std[IN] = STDIN_FILENO;
				data->std[OUT] = STDOUT_FILENO;
				g_sign = 0;
				continue ;
			}
			data->cmd_current = data->cmd_head;
			/*----------------------------------TEMP----------------------------------------------*/
			// t_cmd *currentll = data->cmd_head;
			// while (currentll != NULL)
			// {
			// 	int i = 0;
			// 	if (currentll->cmd)
			// 	{
			// 		while(currentll->cmd[i])
			// 		{
			// 			printf("This is cmd[%i]: %s - %p\n", i, currentll->cmd[i], currentll->cmd[i]);
			// 			i++;
			// 		}
			// 	}
			// 	printf("This is fd_in: %i\n", currentll->fd_in);
			// 	printf("This is fd_out: %i\n", currentll->fd_out);
			// 	printf("This is infile: %s\n", currentll->infile);
			// 	printf("This is outfile: %s\n\n\n", currentll->outfile);
			// 	// printf("Nbr pipes: %i\n", data->nbr_pipes);
			// 	currentll = currentll->pipe;
			// }
			/*----------------------------------TEMP----------------------------------------------*/
			if (token_list)
			{
				free_token_list(token_list);
				token_list = NULL;
			}
			if (data->cmd_head->cmd)
			{
				if (exec(data) == 9)
					return ;
			}
			if (data->cmd_head)
			{
				free_cmd_list(data->cmd_head);
				data->cmd_head = NULL;
			}
			data->nbr_pipes = 0;
			data->std[IN] = STDIN_FILENO;
			data->std[OUT] = STDOUT_FILENO;
			if (g_sign == SIGINT)
				data->exit_code = g_sign + 128;
		}
	}
}
