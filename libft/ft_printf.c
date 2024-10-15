/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 10:40:09 by mstencel      #+#    #+#                 */
/*   Updated: 2024/07/26 09:06:34 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char a)
{
	long	count;

	count = write(1, &a, sizeof(char));
	return (count);
}

int	ft_putstr(char *s)
{
	long	count;
	int		len;

	if (!s)
	{
		count = write(1, "(null)", 6);
		return (count);
	}
	len = ft_strlen(s);
	count = write(1, s, len);
	return (count);
}

static int	arg_check(va_list arg_p, char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(arg_p, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(arg_p, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnum(va_arg(arg_p, int)));
	else if (format == '%')
		return (write(1, "%%", 1));
	else if (format == 'u')
		return (ft_u_int(va_arg(arg_p, unsigned int)));
	else if (format == 'x')
		return (ft_hex(va_arg(arg_p, unsigned int), 'x'));
	else if (format == 'X')
		return (ft_hex(va_arg(arg_p, unsigned int), 'X'));
	else if (format == 'p')
		return (ft_pt_address(va_arg(arg_p, char *)));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_p;
	long	count;
	size_t	i;

	i = 0;
	va_start(arg_p, format);
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += arg_check(arg_p, format[i]);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_arg(arg_p, int);
	va_end (arg_p);
	return (count);
}

// #include <limits.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		n;
// 	char	*str = "abcdefg";
// 	int		a;
// 	int		nb = INT_MIN;
// 	char	*p = "";
// 	char	*ptr = NULL;
// 	// char	*p = LONG_MIN;
// 	// char	*ptr = LONG_MAX;
// 	a = str[0];
// 	n = ft_printf("my char: %c\n my str: %s\n my d: %d\n my i: %i\n
// 		my u: %u\n my l_hex: %x\n my u_hex: %X\n my p: %p\n my p2: %p\n
// 		my percent: %%\n multpile: %c%%%s%%%d%%%u%%%%%%%%%p",
// 		a, str, nb, nb, nb, nb, nb, p, ptr, a, str, nb, nb, ptr);
// 	ft_printf("\n\n");
// 	ft_printf("char count: %i\n\n\n\n", n);
// 	n = ("my char: %c\n my str: %s\n my d: %d\n my i: %i\n
// 		my u: %u\n my l_hex: %x\n my u_hex: %X\n my p: %p\n my p2: %p\n
// 		my percent: %%\n multpile: %c%%%s%%%d%%%u%%%%%%%%%p",
// 		a, str, nb, nb, nb, nb, nb, p, ptr, a, str, nb, nb, ptr);
// 	printf("\n\n");
// 	printf("char count: %i\n", n);
// 	return (0);
// }
