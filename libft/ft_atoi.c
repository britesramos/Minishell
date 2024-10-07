/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 10:34:22 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/26 11:34:03 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	ft_check(const char *nptr)
{
	int	sign;

	sign = 1;
	if (*nptr == '-')
		sign *= -1;
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	digit;
	int	number;

	digit = 0;
	number = 0;
	while (ft_isspace(*nptr))
		nptr++;
	sign = ft_check(nptr);
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		number += digit;
		nptr++;
		if ((ft_isdigit(*nptr)))
			number *= 10;
	}
	return (number *= sign);
}
// int	main(void)
// {
// 	char	*str = " 	\r-2147483648i";

// 	printf("%d\n", atoi(str));
// 	printf("%d\n", ft_atoi(str));
// 	return (0);
// }

// int	main(void)
// {
// 	// char escape[] = {9, 10, 11, 12, 13, 0, "+1"};
// 	// char	escape[] = " +1";
// 	// char	escape[] = " +42lyon";
// 	char	escape[] = "";

// 	printf("%d\n", ft_atoi(escape));
// 	printf("%d\n", atoi(escape));

// 	return (0);
// }