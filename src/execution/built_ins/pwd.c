/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:37:21 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 14:48:21 by mstencel         ###   ########.fr       */
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

int	ft_pwd(char **argv)
{
	char	path[PATH_MAX + 1];
	int		i;

	i = 0;
	//redundant???
	// if (argv[2] && argv[2][0] == '-')
	// {
	// 	write(2, "bash: pwd: -", 13);
	// 	write(2, &argv[2][1], 1);
	// 	write(2, ": invalid option", 17);
	// 	write(2, "\n", 1);
	// 	write(2, "pwd: usage: pwd",16);
	// 	write(2, "\n", 1);
	// 	return (2);
	// }
	if (getcwd(path, sizeof(path)) != NULL)
	{
		while (path[i])
		{
			write(1, &path[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	else
	{
		write(2, "pwd: getcwd() error\n", 21);
		return (1);
	}
	return (0);
	
}