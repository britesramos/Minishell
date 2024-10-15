/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 13:39:05 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:19 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
// // int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = 159;
// 	b = 'a';

// 	printf("%i\n", ft_isascii(a));
// 	printf("%i\n", isascii(a));
// 	printf("%i\n", ft_isascii(b));
// 	printf("%i\n", isascii(b));

// 	return (0);
// }
//checks if int c is between 0-127 (standard ascii)
