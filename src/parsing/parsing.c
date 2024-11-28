/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/28 11:58:09 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_sign;

static int	parsing_helper(t_data *data)
{
	expansion(data);
	tokenization(data);
	if (parse_input(data, data->token_list) == 9)
	{
		clean_up_parse_input(data, data->token_list);
		if (data->token_list)
		{
			free_token_list(data->token_list);
			data->token_list = NULL;
		}
		g_sign = 0;
		return (9);
	}
	if (data->token_list)
	{
		free_token_list(data->token_list);
		data->token_list = NULL;
	}
	return (0);
}

static int	parsing_helper_execution(t_data *data)
{
	if (exec(data) == 9)
		return (9);
	clean_up_parse_input(data, NULL);
	if (g_sign == SIGINT)
		data->exit_code = g_sign + 128;
	return (0);
}

static int	check_line(t_data *data)
{
	if (data->line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (9);
	}
	if (!data->line[0])
		return (1);
	if (data->line[0])
		add_history(data->line);
	return (0);
}

void	parsing(t_data *data)
{
	int	check;

	check = 0;
	ms_signals(INTERACTIVE);
	while (1)
	{
		g_sign = 0;
		if (data->line)
			ft_free_string(&data->line);
		data->line = readline("minishell:~$ ");
		if (g_sign == SIGINT)
			data->exit_code = 128 + g_sign;
		check = check_line(data);
		if (check == 9)
			return ;
		else if (check == 1)
			continue ;
		if (!only_spaces(data) && input_checker(data, data->line) == 0)
		{
			if (parsing_helper(data) == 9)
				continue ;
			if (parsing_helper_execution(data) == 9)
				return ;
		}
	}
}
