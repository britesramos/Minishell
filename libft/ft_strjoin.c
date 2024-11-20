/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 11:00:32 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/19 12:04:19 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	tot_len;
	int		s1_len;
	int		s2_len;

	newstr = NULL;
	if (!s1)
		s1 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tot_len = s1_len + s2_len + 1;
	newstr = malloc(tot_len * sizeof(char));
	if (!newstr)
		return (NULL);
	if (s1)
		ft_strlcpy(newstr, s1, tot_len);
	if (s2)
		ft_strlcat(newstr, s2, tot_len);
	return (newstr);
}

// #include <stdint.h>
// int	main(void)
// {
// 	char	*str1 = "Hello ";
// 	char	*str2 = "";
// 	char	*news = ft_strjoin(str1, str2);

// 	printf("%s\n", news);
// 	printf("%u\n", (unsigned int)(uintptr_t)news);
// 	printf("%u\n", (unsigned int)(uintptr_t)news + news - 1);
// 	printf("%p\n", news);
// 	free(news);
// 	return (0);
// }