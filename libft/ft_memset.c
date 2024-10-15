/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 09:12:50 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 13:53:00 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	b;

	a = (unsigned char *)s;
	b = (unsigned char)c;
	while (n != 0)
	{
		*a = b;
		a++;
		n--;
	}
	return (s);
}
// int	main(void)
// {
// 	char	string[] = "and here we go again\n";

// 	printf("%s", string);
// 	memset(string + 3, '|', 12*sizeof(char));
// 	printf("%s", string);
// 	ft_memset(string + 3, '_', 12*sizeof(char));
// 	printf("%s", string);
// 	return (0);
// }

// //it fills with the 'c' the 'n' number of bytes 
// // starting at the '*s' string's point [memory area] 

// // or shorter version
// {
// 	unsigned char	*a;

// 	a = (unsigned char *)s;
// 	while (n--)
// 		*a++ = (unsigned char)c;
// 	return (s);
// }