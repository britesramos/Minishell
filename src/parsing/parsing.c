/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/15 18:23:52 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_data *data, char **envp)
{
	while (1)
	{
		if (data->line)
			free(data->line);
		data->line = NULL;
		data->line = readline("minishell:~$ ");
		if(data->line[0])
			add_history(data->line);
		input_checker(data);
		parse_input(data);
	}
	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c 
}
