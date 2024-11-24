/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/22 16:00:40 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/24 13:00:24 by mstencel      ########   odam.nl         */
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

// static void	check_tty(void)
// {
// 	if (!isatty(STDIN_FILENO))
// 	{
// 		write (2, "minishell: stdin: not a tty\n", 28);
// 		exit (EXIT_FAILURE);
// 	}
// 	if (!isatty(STDOUT_FILENO))
// 	{
// 		write (2, "minishell: stdout: not a tty\n", 29);
// 		exit (EXIT_FAILURE);
// 	}
// 	if (!isatty(STDERR_FILENO))
// 	{
// 		write (2, "minishell: stderr: not a tty\n", 29);
// 		exit (EXIT_FAILURE);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc == 1)
	{
		// check_tty();
		data = malloc(sizeof(t_data));
		ms_signals(INTERACTIVE);
		if (g_sign == SIGINT)
		{
			ft_putstr_fd("in main?\n", STDOUT_FILENO);
			data->exit_code = 130;
		}
		init_main_struct(data, envp);
		parsing(data, envp);
		return (bye(data));
	}
}
