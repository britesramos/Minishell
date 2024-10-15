/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:41:06 by mstencel      #+#    #+#                 */
/*   Updated: 2023/11/01 15:55:44 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > s_len)
		return (ft_substr(s, 0, 0));
	else if (len > s_len - start)
		len = s_len - start;
	substr = NULL;
	substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
// int	main(void)
// {
// 	char			*str = "my test is here";
// 	unsigned int	n = 3;
// 	size_t			len = 20;
// 	char			*subs = NULL;

// 	subs = ft_substr(str, n, len);
// 	printf("%s\n", subs);
// 	free(subs);
// 	return (0);
// }

// int	main(void)
// {
// 	char *s = ft_substr("tripouille", 100, 1);

// 	printf("%s\n", s);
// 	printf("%d\n", (!strcmp(s, "r")));
// 	return (0);
// }