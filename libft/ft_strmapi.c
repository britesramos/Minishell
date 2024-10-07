/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 12:35:45 by mstencel      #+#    #+#                 */
/*   Updated: 2024/07/26 09:10:25 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*output;
	int		i;
	int		len;

	output = NULL;
	len = ft_strlen(s);
	output = malloc((len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (s[i])
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
// static char	f(unsigned int i, char a)
// {
//	i = 0;
// 	return (a + 1);
// }

// int	main(void)
// {
// 	char	*str = "12345";
// 	char	*change = ft_strmapi(str, f);
// 	printf("%s\n", change);
// 	free(change);
// 	return (0);
// }