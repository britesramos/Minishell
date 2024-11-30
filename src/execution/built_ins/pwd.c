/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 18:37:21 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 15:33:07 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(char **cmd, t_data *data, int fd)
{
	char	path[PATH_MAX + 1];

	if (cmd[1] && cmd[1][0] == '-')
	{
		mini_error(*cmd, ": invalid option: usage: pwd [no options allowed])",\
			 data);
		data->exit_code = 2;
		return ;
	}
	if (getcwd(path, sizeof(path)) != NULL)
		ft_putendl_fd(path, fd);
	else
	{
		ft_putendl_fd("pwd: getcwd() failed", STDERR_FILENO);
		data->exit_code = 2;
	}
	data->exit_code = 0;
}

/*from the bash man:
Print the absolute pathname of the current working directory.
The return status is zero unless an error is encountered while 
determining the name of the current directory or an invalid 
option is supplied.*/

/*
testing on:
1. pwd
2. pwd hello
3. pwd -dsafds
				bash: pwd: -d: invalid option
				pwd: usage: pwd [-LP]
4. pwd -fdsfs
5. /bin/pwd fdsfs -->it will be handled directly by the system
				/bin/pwd: ignoring non-option arguments
				/home/mstencel/Documents/minishell
6. deleting the current folder and the folder above (cd) moving back one
	  folder and pwd there -> should append the .. to the current path
STEPS:
	-> mstencel@c2r2s8:~/Documents/test/test1/test2$ pwd
	/home/mstencel/Documents/test/test1/test2 -> deleted everyting from test
	
-> mstencel@c2r2s8:~/Documents/test/test1/test2$ cd ..
	cd: error retrieving current directory: getcwd: cannot access parent 
									directories: No such file or directory
	
-> mstencel@c2r2s8:~/Documents/test/test1/test2/..$ cd ..
	cd: error retrieving current directory: getcwd: cannot access parent
									directories: No such file or directory
	
-> mstencel@c2r2s8:~/Documents/test/test1/test2/../..$ pwd
	/home/mstencel/Documents/test/test1/test2/../..
	mstencel@c2r2s8:~/Documents/test/test1/test2/../..$ cd ..
	mstencel@c2r2s8:~/Documents$
*/
