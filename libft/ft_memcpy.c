/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 10:16:01 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 13:56:51 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
// int	main(void)
// {
// 	char	src_str[] = "original source";
// 	char	dest_str[] = "original dest";
// 	char	src_str1[] = "my source version";
// 	char	dest_str1[] = "my destination version";

// 	printf("1: %s\n", dest_str);
// 	printf("2: %s\n", dest_str1);
// 	memcpy(dest_str, src_str, 20);
// 	printf("3: %s\n", dest_str);
// 	printf("4: %s\n", (char *)ft_memcpy(dest_str1, src_str1, 25));
// 	printf("5: %s\n", dest_str1);
// 	return (0);
// }

// -> copies n bytes from src memory area to dst memory area 
// -> the memories must not overlap

// NOTE: employing memcpy() with  overlapping  areas  produces 
// undefined  behavior

// (unsigned char *)dest[i] = (unsigned char *)src[i] -> WRONG CASTING
// casting error before: 
// operand of type 'void' where arithmetic or pointer type is required

// In (unsigned char *)dest[i] the (unsigned char *) part has 
// lower precedence than the [i] part, so the compiler tries 
// to evaluate dest[i] first.
// Then the compiler cannot calculate dest[i] because void* does not
// point to an item of a known size. The compiler does not know
// how large dest[i] is

// {
// 	unsigned char	*a;
// 	unsigned char	*b;

// 	a = (unsigned char *)dest;
// 	b = (unsigned char *)src;

// 	while (n != 0)
// 	{
// 		*a = *b;
// 		a++;
// 		b++;
// 		n--;
// 	}
// 	return (dest);
// }