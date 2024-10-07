/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:03:10 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/01 11:28:27 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (n)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
		n--;
	}
	return (0);
}

// int main(void)
// {

//     char s2[] = {};
//     char s3[] = {0, 0, 42, 0};

//     printf("%d\n", ft_memcmp(s2, s3, 4));
// 	printf("%d\n", memcmp(s2, s3, 4));

//     return (0);
// }
// int	main(void)
// {
// 	char	str[] = "Hello";
// 	char	str1[] = "Hellos";
// 	size_t	n = 5;

// 	printf("%d\n", memcmp(str1, str, n));
// 	printf("%d\n", ft_memcmp(str1, str, n));
// 	return (0);
// }