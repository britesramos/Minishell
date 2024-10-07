/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 17:39:24 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/07 08:07:09 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		ft_exit(char **cmd)
{
	if (cmd)
		ft_printf("hello\n");
	//how to get the status code of the previous functions?save in the struct?
	return (0);
}

// from the bash man:
// Exit the shell, returning a status of n to the shell’s parent. 
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.