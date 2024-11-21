/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:13 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/21 11:31:17 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_sign;

int	bye(t_data *data)
{
	int	exit_code;

	if (data->exit_code > 255)
	{
		exit_code = data->exit_code % 256;
		data->exit_code = exit_code;
	}
	else
		exit_code = data->exit_code;
	clean_up(data);
	return (exit_code);
}

static void	check_tty(void)
{
	if (!isatty(STDIN_FILENO))
	{
		write (2, "minishell: stdin: not a tty\n", 28);
		exit (EXIT_FAILURE);
	}
	if (!isatty(STDOUT_FILENO))
	{
		write (2, "minishell: stdout: not a tty\n", 29);
		exit (EXIT_FAILURE);
	}
	if (!isatty(STDERR_FILENO))
	{
		write (2, "minishell: stderr: not a tty\n", 29);
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	check_tty();
	(void)argv; //Not going to use this. Waiting for user prompt.
	data = malloc(sizeof(t_data));
	ms_signals(INTERACTIVE);
	if (g_sign == SIGINT)
	{
		ft_putstr_fd("in main?\n", STDOUT_FILENO);
		data->exit_code = 130;
	}
	init_main_struct(data, envp);
	if (argc < 1) //for execution testing only, to be deleted!
	{
		write(2, "Invalid number of arguments. Type: minishell\n", 45);
		return(1);
	}
	parsing(data, envp);
	return (bye(data));
}