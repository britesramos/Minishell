/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:37:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/07/26 09:19:21 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	little_len = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (*big)
	{
		if (len < little_len)
			return (NULL);
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *) big);
		big++;
		len--;
	}
	return (NULL);
}
// # include <bsd/string.h>
// int	main(void)
// {
// 	// char	*big = "searching here";
// 	// char	*little = "";
// 	// size_t	n = 7;

// 	// printf("%s\n", strnstr(big, little, n));
// 	// printf("%s\n", ft_strnstr(big, little, n));

// 	// size_t	n = -1;
// 	char big[30] = "aaabcabcd";
// 	char small[10] = "aabc";
// 	// char * empty = (char*)"";
// 	//1
// 	printf("1: %s\n", strnstr(big, small, 0));
// 	printf("1: %s\n", ft_strnstr(big, small, 0));
// 	//2
// 	printf("2: %s\n", strnstr(big, small, -1));
// 	printf("2: %s\n", ft_strnstr(big, small, -1));
// 	//When you pass -1 to strnstr, it is interpreted as the maximum value that
// 	// size_t can hold, because -1 is a common way to represent 
//  // the maximum value
// 	// of an unsigned integer type in C. This is due to how two's complement
// 	// representation works, where -1 is represented as all 1s, which is the
// 	// maximum value for an unsigned integer
// 	//3
// 	printf("3: %s\n", strnstr(big, "a", -1));
// 	printf("3: %s\n", ft_strnstr(big, "a", -1));
// 	//4
// 	printf("4: %s\n", strnstr(big, "c", -1));
// 	printf("4: %s\n", ft_strnstr(big, "c", -1));
// 	//10
// 	printf("10: %s\n", strnstr(big, "abcd", 9));
// 	printf("10: %s\n", ft_strnstr(big, "abcd", 9));

// 	return (0);
// }
// // cc -Werror -Wextra -Wall ft_strnstr.c -lbsd 