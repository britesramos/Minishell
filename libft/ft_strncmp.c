/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:45:56 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 12:22:13 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && n != 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		n--;
	}
	return (0);
}
// int	main(void)
// {
// 	char	str1[] = "qwert0";
// 	char	str2[] = "qwetr0a";
// 	size_t	i = 6;

// 	printf("%d\n", strncmp(str1, str2, i));
// 	printf("%d\n", ft_strncmp(str1, str2, i));

// 	return (0);
// }

//  The strncmp() function is similar, except it compares only the first (at
//  most) n bytes of s1 and s2.