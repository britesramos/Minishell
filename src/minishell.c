/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:13 by sramos            #+#    #+#             */
/*   Updated: 2024/09/26 11:48:59 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	init_main_struct(data);
	if (argc > 1)
	{
		write(1, "Invalid number of arguments. Type: minishell\n", 45);
		return(1);
	}
	data->line = readline(argv[1]); /*There are leaks here from readline, but I dont know if it is fixable.*/
	parsing(data, envp);

	
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
	clean_up(data);
	return (0);
}