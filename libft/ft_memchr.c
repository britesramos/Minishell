/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 18:00:44 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 13:37:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (n > 0)
	{
		if (*a == (unsigned char)c)
			return ((unsigned char *)a);
		a++;
		n--;
	}
	return (0);
}
// #include <stdint.h>
// int	main(void)
// {
// 	char	*str = "this@is my string12346";
// 	int		a = 'g';
// 	size_t	n = 18;

// 	printf("%s\n%ld\n", (char *)memchr(str, a, n),
// 		((char *)memchr(str, a, n) - str + 1));
// 	printf("%s\n%ld\n", (char *)ft_memchr(str, a, n),
// 		((char *)ft_memchr(str, a, n) - str + 1));
// 	// printf("%p\n", (void *)str);
// 	// printf("%p\n", (void *)ft_memchr(str, a, n));
// 	// printf("%p\n", (void *)memchr(str, a, n));
// 	printf("%u\n", (unsigned int)(uintptr_t)str);
// 	printf("%u\n", (unsigned int)(uintptr_t)ft_memchr(str, a, n));
// 	return (0);
// }

// it will scan the entire block of memory regardless 
//of the presence of null characters
// needs #include <stdint.h> for uintptr_t

// uintptr_t is an unsigned integer type that is capable 
// of storing a data pointer
// (whether it can hold a function pointer is unspecified). 
// Which typically means that it's the same size as a pointer.