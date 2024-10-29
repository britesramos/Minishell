/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 16:55:05 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 11:05:50 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_size;
	char	*s2;
	int		len;

	len = ft_strlen(s);
	s_size = len + 1;
	s2 = NULL;
	s2 = (char *)malloc((s_size) * sizeof(char));
	if (!s2)
		return (0);
	ft_strlcpy(s2, s, s_size);
	return (s2);
}
// int	main(void)
// {
// 	const char	*str = "my string";
// 	const char	*str2;
// 	const char	*str3;

// 	str2 = strdup(str);
// 	printf("%s\n", str2);
// 	str3 = ft_strdup(str);
// 	printf("%s\n", str3);
// 	return (0);
// 	free((void *)str2);
// 	free((void *)str3);
// }

//The strdup() function returns a pointer to a new string which is 
//	a duplicate of the string s. Memory for the new string  is 
//	obtained with malloc(3), and can be freed with free(3).