/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 18:37:21 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/10 08:13:04 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// testing on:
// 1. pwd
// 2. pwd hello
// 3. pwd -dsafds
//				bash: pwd: -d: invalid option
// 				pwd: usage: pwd [-LP]
// 4. pwd -fdsfs
// 5. /bin/pwd fdsfs -->it will be handled directly by the system
// 				/bin/pwd: ignoring non-option arguments
// 				/home/mstencel/Documents/minishell
// 6. deleting the current folder and the folder above (cd) moving to the previous 
//	  folder and pwd there -> should append the .. to the current path
//				-> mstencel@c2r2s8:~/Documents/test/test1/test2$ pwd
// 				/home/mstencel/Documents/test/test1/test2 -> deleted everyting from test onwards
// 				-> mstencel@c2r2s8:~/Documents/test/test1/test2$ cd ..
// 				cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// 				-> mstencel@c2r2s8:~/Documents/test/test1/test2/..$ cd ..
// 				cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// 				-> mstencel@c2r2s8:~/Documents/test/test1/test2/../..$ pwd
// 				/home/mstencel/Documents/test/test1/test2/../..
// 				mstencel@c2r2s8:~/Documents/test/test1/test2/../..$ cd ..
// 				mstencel@c2r2s8:~/Documents$

int	ft_pwd(char **argv, t_data *data)
{
	char	path[PATH_MAX + 1];
	int		i;
	
	i = 0;
	if (argv[1] && argv[1][0] == '-')
	{
		ft_putstr_fd("bash: pwd: -", STDERR_FILENO);
		ft_putchar_fd(argv[1][1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\npwd: usage: pwd [no options allowed]\n", STDERR_FILENO);
		return (2);
	}
	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, data->cmd_current->fd_out);
		ft_putchar_fd('\n', data->cmd_current->fd_out);
	}
	else
	{
		ft_putstr_fd("pwd: getcwd() failed\n", STDERR_FILENO);
		return (2);
	}
	return (0);
	
}

// from the bash man:
// Print the absolute pathname of the current working directory.
// The return status is zero unless an error is encountered while 
// determining the name of the current directory or an invalid 
// option is supplied.