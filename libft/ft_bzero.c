/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:04:35 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (n)
	{
		*a = '\0';
		a++;
		n--;
	}
}
// int	main(void)
// {
	// char string[] = "yet another one";
	// char string1[] = "yet another one";

	// printf("%s\n", string);
	// bzero(string + 3, 21*sizeof(char));
	// printf("%s\n", string);
	// printf("%c\n", string[25]);
// 	printf("%s\n", string1);
// 	ft_bzero(string1 + 3, 21*sizeof(char));
// 	printf("%s\n", string1);
// 	printf("%c\n", string1[25]);
// 	return (0);
// }

//	-> it errases the 'n' bytes of memory by writing zeros ('\0') 
//	-> it starts at the *s location [basically, memset() with '\0' as the fill]
// NOTE: for the check of a single char use -> ./a.out | cat -A  