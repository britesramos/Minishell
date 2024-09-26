/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:05:25 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 14:49:06 by mstencel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (s1[i] || s2[i])
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}

int	ft_t_check(char **cmd)
{
	//change the index & text once you get the proper input from the program
	if (ft_strcmp(cmd[1], "my_echo") == 0)
		return (ft_echo(cmd), 0);
	else if (ft_strcmp(cmd[1], "my_pwd") == 0)
		return (ft_pwd(cmd), 0);
	return (0);
}
