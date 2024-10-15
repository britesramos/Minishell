/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 11:42:02 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/21 12:13:23 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (src_len + size);
	while (src[i] && (dst_len + i) < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
// # include <bsd/string.h>
// int	main(void)
// {
// 	char src[20] = "source";
// 	char dst[] = "";
// 	char src1[20] = "source";
// 	char dst1[] = "";

// 	printf("%zu\n", strlcat(dst, src, sizeof(dst)));
// 	printf("%s\n", dst);
// 	printf("%zu\n", ft_strlcat(dst1, src1, sizeof(dst1)));
// 	printf("%s\n", dst1);

	// char dest[30]; memset(dest, 0, 30);
	// char * src = (char *)"AAAAAAAAA";
	// memset(dest, 'B', 4);
	// printf("%zu\n", ft_strlcat(dest, src, 6));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, src, 6));
	// printf("%s\n", dest);
	// printf("%zu\n", ft_strlcat(dest, src, 3));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, src, 3));
	// printf("%s\n", dest);
	// memset(dest, 'C', 5);
	// printf("%zu\n", ft_strlcat(dest, src, -1));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, src, -1));
	// printf("%s\n", dest);
	// memset(dest, 'C', 15);
	// printf("%zu\n", ft_strlcat(dest, src, 17));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, src, 17));
	// printf("%s\n", dest);
	// memset(dest, 0, 30);
	// printf("%zu\n", ft_strlcat(dest, src, 1));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, src, 1));
	// printf("%s\n", dest);
	// memset(dest, 0, 30);
	// printf("%zu\n", ft_strlcat(dest, "123", 1));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, "123", 1));
	// printf("%s\n", dest);
	// memset(dest, 0, 30);
	// printf("%zu\n", ft_strlcat(dest, "123", 2));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, "123", 2));
	// printf("%s\n", dest);
	// memset(dest, 0, 30);
	// printf("%zu\n", ft_strlcat(dest, "123", 3));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcat(dest, "123", 3));
	// printf("%s\n", dest);
// 	return (0);
// }

// cc -Werror -Wextra -Wall ft_strlcat.c ft_strlen.c -lbsd