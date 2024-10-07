/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_extra.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 11:10:49 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/04 13:12:42 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnum(int n)
{
	long	count;
	long	num;
	char	a;

	count = 0;
	num = n;
	if (n < 0)
	{
		count += write(1, "-", 1);
		num *= -1;
	}
	if (num > 9)
		count += ft_putnum(num / 10);
	a = num % 10 + '0';
	count += write(1, &a, sizeof(char));
	return (count);
}

int	ft_u_int(unsigned int number)
{
	long	num;
	char	a;
	long	count;

	count = 0;
	num = number;
	if (num > 9)
		count = ft_u_int(num / 10);
	a = num % 10 + '0';
	write(1, &a, sizeof(char));
	return (count + 1);
}

int	ft_hex(unsigned int value, int base)
{
	char	*my_base;
	long	count;

	count = 0;
	my_base = NULL;
	if (base == 'x')
		my_base = "0123456789abcdef";
	else if (base == 'X')
		my_base = "0123456789ABCDEF";
	if (value > 15)
		count = ft_hex(value / 16, base);
	write(1, &my_base[value % 16], sizeof(char));
	return (count + 1);
}

int	ft_ptr_help(size_t value)
{
	char	*my_base;
	long	count;

	count = 0;
	my_base = "0123456789abcdef";
	if (value > 15)
		count = ft_ptr_help(value / 16);
	write(1, &my_base[value % 16], sizeof(char));
	return (count + 1);
}

int	ft_pt_address(char *ptr)
{
	long	count;
	size_t	my_p;

	count = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	else
	{
		count += write(1, "0x", 2);
		my_p = (size_t)ptr;
		count += ft_ptr_help(my_p);
	}
	return (count);
}
