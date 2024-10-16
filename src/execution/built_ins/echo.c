/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 12:10:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/16 11:08:05 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
testing on:
echo -nnnn "Hello    that's what    needs to " be checked...
echo -nnn -nnna
echo Hello -nnn
echo -rrrrr 'Hello World that's why

TODO: //or is it in parsing-expansion?
echo $? -> prints the exit code from the last program - do we store it as a global variable or keep in the 
echo $$ -> prints the ppid
echo "$PWD"   ->  /home/mstencel/Documents/Minishell_sara_git/sara_git
echo '$PWD'   -> $PWD
echo "'$PWD'" -> '/home/mstencel/Documents/Minishell_sara_git/sara_git'
echo '"$PWD"' -> "$PWD"
echo $PWDDDD / echo "$PWDDDD"  ->returns an empty new line
echo "'$PWDDDDDDD'" -> ''

TODO - add the quotes handling ->for parsing?
TODO - add the envp's
TODO - handle errors - here or in ft_putchar_fd?
TODO - for fd_out - pass the cmd_current in the previous function?
*/

#include <stdio.h>

/// @brief
//returns 0 when there is no new line at the end (flag -n is used);
//returns 1 when there is the new line at the end
int	has_new_line(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	if (cmd[i] == '-')
		i++;
	while (cmd[i] == 'n')
		i++;
	if (i == len)
		return (0);
	else
		return (1);
}

///@brief from the bash man: Output the args, separated by spaces, 
// terminated with a newline.
// The return status is 0 unless a write error occurs. 
// If -n is specified, the trailing newline is suppressed.
// 	nl = new_line check (1 when there is a new line and 0 when there is the flag -n)
int	ft_echo(char **cmd, t_data *data)
{
	int	nl;
	int	i;

	i = 1;
	if (cmd[i] == NULL)
	{
		ft_putstr_fd("", data->cmd_current->fd_out);
		data->exit_code = 1;
	}
	nl = has_new_line(cmd[i]);
	if (nl == 0)
		i++;
	// ft_echo_work(data);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], data->cmd_current->fd_out);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', data->cmd_current->fd_out);
	}
	if (nl == 1)
		ft_putchar_fd('\n', data->cmd_current->fd_out);
	data->exit_code = 0;
	return (0);
}

// from the bash man
// Output the args, separated by spaces, terminated with a newline.
// The return status is 0 unless a write error occurs. 
// If -n is specified, the trailing newline is suppressed.