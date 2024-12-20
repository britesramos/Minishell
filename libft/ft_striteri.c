/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 14:13:36 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/03 13:32:10 by mstencel      ########   odam.nl         */
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

// void	f(unsigned int i, char *a)
// {
// 	i = 0;
// 	i++;
// 	*a = *a + 1;
// }

// int	main(void)
// {
// 	char	str[] = "ABCDEFG";
// 	ft_striteri(str, f);
// 	printf("%s\n", str);
// 	return (0);
// }