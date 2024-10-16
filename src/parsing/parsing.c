/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:18 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/11 09:29:42 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_data *data, char **envp)
{
	// invalid_input(data);
	parse_envp(data, envp); //There is leaks from here. But I am not sure why. See clean_up.c


	//3 - Tokenization
	//4 - Parsed input
}
