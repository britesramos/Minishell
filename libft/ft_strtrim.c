/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 15:00:45 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 12:25:05 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	i;
	size_t	end;
	int		total_len;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	total_len = end - i + 1;
	if (total_len < 0)
		total_len = 0;
	new_str = NULL;
	new_str = malloc(sizeof(char) * total_len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1 + i, total_len + 1);
	return (new_str);
}
// int	main(void)
// {
// 	char	*str = "!?!...my example..!?!";
// 	char	*set = "!?.";
// 	char	*nstr = NULL;

// 	nstr = ft_strtrim(str, set);
// 	printf("%s\n", str);
// 	printf("%s\n", nstr);
// 	free(nstr);
// 	return(0);
// }