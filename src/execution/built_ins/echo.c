/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 12:10:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/15 09:04:05 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_echo_print(int i, char **cmd, int fd)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', fd);
	}
}

/// @brief returns 0 there is no new line at the end (flag -n is used);
//returns 1 there is the new line at the end
static int	has_new_line(char *cmd)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (cmd[0] == '-' && cmd[1] == 'n')
	{
		while (cmd[i] && cmd[i] == 'n')
			i++;
		if (cmd[i] == '\0')
			check = 1;
	}
	if (check == 1)
		return (0);
	else
		return (1);
}

///@brief from the bash man: Output the args, separated by spaces, 
// terminated with a newline.
// The return status is 0 unless a write error occurs. 
// If -n is specified, the trailing newline is suppressed.
// nl = new_line check (1 there is a new line and 0 no new line - flag -n)
void	ft_echo(char **cmd, t_data *data, int fd)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (cmd[i] == NULL)
	{
		ft_putstr_fd("\n", fd);
		data->exit_code = 0;
		return ;
	}
	while (has_new_line(cmd[i]) == 0)
		i++;
	if (i != 1)
		nl = 0;
	ft_echo_print(i, cmd, fd);
	if (nl == 1)
		ft_putchar_fd('\n', fd);
	data->exit_code = 0;
}

/*
testing on:
echo -nnnn "Hello    that's what    needs to " be checked...
echo -nnn -nnna
echo Hello -nnn
echo -rrrrr 'Hello World that's why
echo -nnn -n -nnnn - n Hello ->the output:  - n Hello

TODO - handle errors - here or in ft_putchar_fd?
*/