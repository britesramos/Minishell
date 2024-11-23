/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 11:21:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/21 13:38:34 by mstencel      ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosia <gosia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:21:27 by mstencel          #+#    #+#             */
/*   Updated: 2024/11/21 20:06:47 by gosia            ###   ########.fr       */
>>>>>>> f7acdb31381e8d7b6e93cb0725d341f2f262343a
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
