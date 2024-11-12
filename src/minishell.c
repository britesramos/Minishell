/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/11 12:41:02 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	bye(t_data *data)
{
	int	exit_code;

	if (data->exit_code > 255)
		exit_code = data->exit_code % 256;
	else
		exit_code = data->exit_code;
	// ft_printf("exit_code in main: %d\n", exit_code);
	clean_up(data);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;
	
	(void)argv; //Not going to use this. Waiting for user prompt.
	data = malloc(sizeof(t_data));
	
	init_main_struct(data, envp);
	if (argc < 1) //for execution testing only, to be deleted!
	{
		write(2, "Invalid number of arguments. Type: minishell\n", 45);
		return(1);
	}
	parsing(data, envp);
	return (bye(data));
}