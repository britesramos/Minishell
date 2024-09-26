/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:39:24 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 19:25:16 by mstencel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ft_exit(char **argv)
// {
// 	//how to get the status code of the previous functions?save in the struct?
// }

// from the bash man:
// Exit the shell, returning a status of n to the shell’s parent. 
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.