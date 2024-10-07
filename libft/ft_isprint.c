/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:20:23 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:04 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = ' ';
// 	b = u'Ö';

// 	printf("%i\n", ft_isprint(a));
// 	printf("%i\n", isprint(a));
// 	printf("%i\n", ft_isprint(b));
// 	printf("%i\n", isprint(b));
// }

// checks if c is a printable (ascii)