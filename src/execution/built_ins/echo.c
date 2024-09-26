/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:10:27 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 18:44:03 by mstencel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
testing on:
echo -nnnn "Hello    that's what    needs to " be checked...
echo -nnn -nnna
echo Hello -nnn
echo $PWDDDD
echo -rrrrr "Hello World that's why ->waiting for the double quote to close
echo -nnnn 'Hello    that's what    needs to ' be checked... ->waiting for the single quote to close
echo -rrrrr 'Hello World that's why
*/


// delete it once libft in live!!!!
#include <stdio.h>

// int	ft_strlength(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

/*
checks if the echo should print the new line at the end
returns 0 when there is no new line (flag -n)
returns 1 when there is the new line
*/
int	has_new_line(char *argv)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(argv);
	if (argv[i] == '-')
		i++;
	while (argv[i] == 'n')
		i++;
	if (i == len)
		return (0);
	else
		return (1);
}

//adjust the num [argv[num]] when Sara gives the input - it will be 1 less
/***
 * i = index
 * nl = new_line check
 * flag = will serve as the index number of the argument that needs to be 
 * 		printed
 * check = checks when the function should start printing (so it's not the flag -n anymore)
 * 
 * sets the new_line flag on 1 if there is new line or 0 if the -n is used
 * writes the arguments that should be out
 * writes the 
*/

void	ft_echo(char **argv)
{
	//TODO? - create an array of ints?
	int		i;
	int		nl;
	int		flag;
	int		check;
	// char	*env;
	// int	is_env; -> for writing the env values

	i = 0;
	flag = 1;
	nl = has_new_line(argv[flag]);
	while (argv[flag])
	{
		check = has_new_line(argv[flag]);
		if (argv[flag][i] == '-' && check == 0)
			flag++;
		else
			break ;
	}
	//use libft functions below
	while (argv[flag])
	{
		i = 0;
		while (argv[flag][i])
		{
			write(1, &argv[flag][i], 1); //how to go about the different fd's when redirecting...
			i++;
		}
		flag++;
		if (argv[flag])
			write(1, " ", 1);
	}
	if (nl == 1)
		write(1, "\n", 1);
}

// from bash man
// Output the args, separated by spaces, terminated with a newline.
// The return status is 0 unless a write error occurs. 
// If -n is specified, the trailing newline is suppressed. I