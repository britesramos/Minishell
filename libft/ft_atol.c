/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 14:44:48 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/22 07:24:03 by mstencel      ########   odam.nl         */
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

long	ft_atol(const char *nptr)
{
	int		sign;
	long	digit;
	long	number;

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
