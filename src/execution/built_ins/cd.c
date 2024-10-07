/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:01:06 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/07 08:02:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_cd(char **cmd, t_envp *env)
{
	if (strcmp(cmd[1], "..") == 0)
	{
		printf("hello\n");
		//remove the preceding path back to a slash or the beginning of dir
		
		//go through the list and find the OLDPATH
	}
	if (env)
	{
		ft_printf("hello here\n");
	}
	// if (!cmd[1])
	// {
	// 	printf("hi: *s\n", env->value);
	// }
}

// cd with only a relative or absolute path (starting with /)
// All relative names are treated by the kernel as relative to the current
// directory — as if the name was prefixed by ./

// from the bash man
// cd changes the current working directory to directory given as an argument 
// 1.If directory is not supplied, the value of the HOME shell variable is used
// 2.If the shell variable CDPATH exists, it is used as a search path:
// each directory name in CDPATH is searched for directory, with alternative
// directory names in CDPATH separated by a colon (‘:’).
// 3.If directory begins with a slash, CDPATH is not used.
// 4.If ‘..’ appears in directory, it is processed by removing the immediately
// preceding pathname component, back to a slash or the beginning of directory.
// 5. If directory is ‘-’, it is converted to $OLDPWD before the directory
// change is attempted.
// 6.If a non-empty directory name from CDPATH is used, or if ‘-’ is the first
// argument, and the directory change is successful, the absolute pathname of
// the new working directory is written to the standard output.
// 7.If the directory change is successful, cd sets the value of the PWD
// environment variable to the new directory name, and sets the OLDPWD
// environment variable to the value of the current working directory before
// the change.
// 8.The return status is zero if the directory is successfully changed,
// non-zero otherwise.