/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:11:11 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:24:01 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
// int	main(void)
// {
// 	int	a = 'z';
// 	int	b = 'z';

// 	printf("%c\n", ft_toupper((unsigned char)a));
// 	printf("%c\n", toupper((unsigned char)b));

// 	return (0);
// }