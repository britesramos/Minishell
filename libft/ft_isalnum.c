/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:04:16 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:36 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z'))
		|| ((c >= 'a') && (c <= 'z')));
}
// int main(void)
// {
//     int a;
//     int b;
//     int c;
//     unsigned char d;

//     a = '9';
//     b = 'M';
//     c = 'm';
//     d = '\n';

//     printf("%i\n", ft_isalnum(a));
//     printf("%i\n", isalnum(a));
//     printf("%i\n", ft_isalnum(b));
//     printf("%i\n", isalnum(b));
//     printf("%i\n", ft_isalnum(c));
//     printf("%i\n", isalnum(c));
//     printf("%i\n", ft_isalnum(d));
//     printf("%i\n", isalnum(d));

//     return(0);
// }
//checks if int c is a number or a letter (0-9 / A-Z / a - z)
