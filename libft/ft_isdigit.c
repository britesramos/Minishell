/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:54:52 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/10 14:27:12 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
// int main(void)
// {
//     int a;
//     int b;

//     a = '9';
//     b = 'a';

//     printf("%i\n", ft_isdigit(a));
//     printf("%i\n", isdigit(a));
//     printf("%i\n", ft_isdigit(b));
//     printf("%i\n", isdigit(b));

//     return(0);
// }
//checks if int c is between 0-9