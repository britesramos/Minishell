/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/26 10:45:06 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

void	parsing(t_data *data)
{
	while (1)
	{
		g_sign = 0;
		if (data->line)
			ft_free_string(&data->line);
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
		if (input_checker(data, data->line) == 0 && !only_spaces(data))
		{
			expansion(data);
			tokenization(data);
			printf("data->line: %s\nafter tokanization?\n", data->line);
			/*----------------------------------TEMP----------------------------------------------*/
			// print_token_list(data->token_list);
			/*----------------------------------TEMP----------------------------------------------*/
			if (parse_input(data, data->token_list) == 9)
			{
				clean_up_parse_input(data, data->token_list);
				if (data->token_list)
				{
					free_token_list(data->token_list);
					data->token_list = NULL;
				}
				printf("am I clean?\n");
				g_sign = 0;
				continue ;
			}
			printf("I shouldn't be here\n");
			/*----------------------------------TEMP----------------------------------------------*/
			// print_cmd_list(data);
			/*----------------------------------TEMP----------------------------------------------*/
			if (data->token_list)
			{
				free_token_list(data->token_list);
				data->token_list = NULL;
			}
			if (exec(data) == 9)
				return ;
			clean_up_parse_input(data, NULL);
			if (g_sign == SIGINT)
				data->exit_code = g_sign + 128;
		}
		if (data->line[0])
			add_history(data->line);
	}
}
