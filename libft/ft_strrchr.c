/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:09:39 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/17 16:59:50 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	cc;

	len = 0;
	cc = (unsigned char) c;
	while (s[len])
		len++;
	while (len >= 0)
	{
		if (s[len] == cc)
			return ((char *)&s[len]);
		len--;
	}
	return (0);
}
// int	main(void)
// {
// 	char	*str = "and here is string";
// 	int		a = 'i';

// 	printf("%s\nfound at position %ld\n", strrchr(str, a), 
// 		(strrchr(str, a) - str + 1));
// 	printf("%s\nfound at position %ld\n", ft_strrchr(str, a), 
// 		(ft_strrchr(str, a) - str + 1));

// 	return (0);
// }

//  The strrchr() function returns a pointer to the last occurrence of the
//  character c in the string s.
