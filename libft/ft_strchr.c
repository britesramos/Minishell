/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:41:29 by mstencel      #+#    #+#                 */
/*   Updated: 2024/05/24 14:03:04 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	cc = (unsigned char) c;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}
// int	main(void)
// {
// 	char	str[] = "here is !my string";
// 	// int		a = '!';

// 	printf("%s\nfound at position %ld\n", strchr(str, 0), 
// 		(strchr(str, 0) - str + 1));
// 	printf("%s\nfound at position %ld\n", ft_strchr(str, 0), 
// 		(ft_strchr(str,0) - str + 1));
// 	return (0);
// }

// searcher for a char in the string, if doesn't find it, returns null