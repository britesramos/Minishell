/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 08:52:22 by mstencel      #+#    #+#                 */
/*   Updated: 2024/08/06 11:44:28 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	const char *str;

// 	str = s;
// 	while (*s)
// 		s++;
// 	return (s - str);
// }

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// int	main(void)
// {
// 	char string[] = "an example";

// 	printf("%zu\n", ft_strlen(string));
// 	printf("%zu\n", strlen(string));

// 	return (0);
// }

// -> it calculates the LENGTH (NOT size) of the string excluding '\0'
// -> it returns the number of bytes in the string pointed to by s

// size_t -> represents the size of objects in bytes, is dependent on
// the complier (e.g. complier 32 bit => unsigned int,
// complier 64 bit => unsigned long long)
// size_t in never negative, %z