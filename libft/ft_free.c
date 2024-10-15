/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 11:21:27 by mstencel      #+#    #+#                 */
/*   Updated: 2024/08/06 11:44:11 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
	return (NULL);
}
