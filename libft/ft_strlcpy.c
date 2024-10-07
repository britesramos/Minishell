/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 08:16:35 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/13 10:24:43 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (src[length])
		length++;
	if (size > 0)
	{
		while (src[i] && size - 1)
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
	}
	return (length);
}
//# include <bsd/string.h>
// int	main(void)
// {
// 	char	src[] = "this is my source";
// 	char	dest[] = "and that's the destination";
// 	char	src1[] = "this is my source";
// 	char	dest1[] = "and that's the destination";
// 	size_t	size = 10;

// 	printf("ORIGINAL: %lu\n", strlcpy(dest, src, size));
// 	printf("ORIGINAL: %s\n", dest);
// 	printf("%lu\n", strlcpy(dest1, src1, size));
// 	printf("%s\n", dest1);

// 	return (0);
// }

// as long as size > 0
// -> it copies size - 1 characters from the src string to dest

// -> it always (!) includes '\0' at the end

// -> it uses the full size of the buffer, including '\0' byte in the size

// -> it returns the total length of the src string (so NOT the size!)

// IMPORTANT: to run the <bds/string.h> run the following:
// cc -Werror -Wextra -Wall ft_strlcpy.c -lbsd