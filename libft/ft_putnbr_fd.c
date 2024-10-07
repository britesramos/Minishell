/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:31:51 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 14:03:00 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	a;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	a = n % 10 + '0';
	write(fd, &a, 1);
}
// #include <fcntl.h>
// int	main(void)
// {
// 	int	a = -2147483647;
// 	int	fd;

// 	fd = open("ft_nbr_test.txt", O_RDWR | O_CREAT, 0777);
// 	if (fd == -1)
// 		return(1);
// 	ft_putnbr_fd(a, fd);
// 	printf("fd = %d\n", fd);
// 	close(fd);
// }