/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:49:24 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/20 13:43:13 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long my_n)
{
	int	count;

	count = 0;
	if (my_n == 0)
		return (count + 1);
	if (my_n < 0)
	{
		count += 1;
		my_n *= -1;
	}
	while (my_n > 9)
	{
		count++;
		my_n /= 10;
	}
	return (count + 1);
}

static char	*ft_change(long my_n, char *str)
{
	int	i;

	i = 0;
	if (my_n < 0)
	{
		str[i] = '-';
		i++;
		my_n *= -1;
	}
	while (my_n > 9)
	{
		str[i] = my_n % 10 + '0';
		my_n /= 10;
		i++;
	}
	str[i] = my_n % 10 + '0';
	i++;
	str[i] = '\0';
	return (str);
}

static char	*ft_reverse(char *s, long my_n)
{
	char	a;
	int		end;
	int		start;
	int		len;

	if (my_n < 0)
		start = 1;
	else
		start = 0;
	len = ft_strlen(s);
	end = len - 1;
	while (start < end)
	{
		a = s[start];
		s[start] = s[end];
		s[end] = a;
		start++;
		end--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	my_n;
	int		count;

	s = NULL;
	my_n = n;
	count = ft_count(my_n) + 1;
	s = malloc(sizeof(char) * count);
	if (!s)
		return (NULL);
	ft_change(my_n, s);
	ft_reverse(s, my_n);
	return (s);
}
// #include <limits.h>
// int	main(void)
// {
// 	int	a = 214748364;
// 	char *s = NULL;

// 	s = ft_itoa(a);
// 	printf("%s\n", s);
// 	free(s);
// 	return(0);
// }
