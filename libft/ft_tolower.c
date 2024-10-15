/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:23:59 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:24:10 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
// int	main(void)
// {
// 	int	a = 'Z';
// 	int	b = 'Z';

// 	printf("%c\n", (char)tolower((unsigned char)a));
// 	printf("%c\n", (char)ft_tolower((unsigned char)b));

// 	return (0);
// }