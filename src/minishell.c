/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/15 17:59:50 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data *data;
	int		exit_code;
	
	(void)argv; //Not going to use this. Waiting for user prompt.
	data = malloc(sizeof(t_data));
	init_main_struct(data);
	if (argc > 1)
	{
		write(1, "Invalid number of arguments. Type: minishell\n", 45);
		return(1);
	}
	parsing(data, envp);
	exec(data);
	
	// 1) Readline function. (Malloc every time and also dont forget to free.)
	// 2) Parsing.
		// 2.1) Invalid inputs (syntax errors).
		// 2.2) White spaces.
		// "" ''
		// Position of pipe | beging ...
		// 2.2) env in linked list.
		// 2.3)Tokenize.
	// 3) History. ???
	// 4) Expansion. (echo $USER) ???
	// 5) Execution.
		//5.1.)Built-ins.
		//5.2.)Pipes.
		//5.3.)Redirections
		//5.4.)Signals
	if (data->exit_code > 255)
		exit_code = data->exit_code % 256;
	else
		exit_code = data->exit_code;
	ft_printf("exit_code in main: %d\n", exit_code);
	clean_up(data);
	return (exit_code);
}