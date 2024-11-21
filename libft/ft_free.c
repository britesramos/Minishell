/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosia <gosia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:21:27 by mstencel          #+#    #+#             */
/*   Updated: 2024/11/21 20:06:47 by gosia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
	}
	free(str);
	str = NULL;
}

void	ft_free_string(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
