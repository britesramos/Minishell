/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 14:13:36 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/04 13:33:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

void	f(unsigned int i, char *a)
{
	i = 0;
	*a = *a + 1;
}

// int	main(void)
// {
// 	char	str[] = "ABCDEFG";
// 	ft_striteri(str, f);
// 	printf("%s\n", str);
// 	return (0);
// }