/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 14:17:40 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:28 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
// int main(void)
// {
//     int a;
//     int b;
//     int c;

//     a = 'A';
//     b = 'z';
//     c = 2;

//     printf("%i\n", ft_isalpha(a));
//     printf("%i\n", isalpha(a));
//     printf("%i\n", ft_isalpha(b));
//     printf("%i\n", isalpha(b));
//     printf("%i\n", ft_isalpha(c));
//     printf("%i\n", isalpha(c));

//     return(0);
// }
//checks if int c is between 'A'-'Z' or 'a'-'z'
