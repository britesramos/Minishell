/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/18 19:36:26 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_exit(char *str, int seo)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	//TODO:Clean_up; //Memory leaks from parsing envp might come from here.
	// data.exit_code = seo;
	exit(seo); //Only exit if exit program. Not on errors.
}