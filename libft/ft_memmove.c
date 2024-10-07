/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 10:21:45 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 13:52:06 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (dest == src)
		return (ft_memcpy(d, s, n));
	else if (dest < src)
		ft_memcpy(d, s, n);
	else if (dest > src)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
// int	main(void)
// {
// 	// char	src[] = {'a', 'b', 'c', 'd', 'e'};
// 	char	src[] = "acder a t";
// 	// char	dst[50] = "my dest";
// 	// char	src1[] = {'a', 'b', 'c', 'd', 'e'};
// 	char	src1[] = "acder a t";
// 	// char	dst1[50] = "my dest";

// 	printf("%s\n", (char *)memmove(src + 2, src, 3));
// 	printf("%s\n", (char *)ft_memmove(src1 + 3, src1, 3));
// 	return (0);
// }

// -> copies n bytes from src memory dst
// -> if dst is before src, it copies from the start to the end
// else, it goes from the end to the start

// -> To find the last byte of src and dest add the number of bytes to be 
// copied (n)

// -> the memory may overlap
// -> the behavior is undefined if access occurs beyond 
// the end of the dest array 

// -> the behavior is undefined if either dest or src is 
// an invalid or null pointer.