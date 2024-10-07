/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 17:50:30 by mstencel      #+#    #+#                 */
/*   Updated: 2023/10/29 14:01:31 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
// #include <fcntl.h>
// int	main(void)
// {
// 	char	*a = "Hello";
// 	int		fd;
// 	// int		fd1;
// 	// size_t	a_len = ft_strlen(a);

// 	fd = open("ft_test.txt", O_RDWR | O_CREAT, 0777);
// 	if (fd == -1)
// 		return (1);
// 	printf("fd = %d\n", fd);
// 	while (*a)
// 	{
// 		ft_putchar_fd(*a, fd);
// 		a++;
// 	}
// 	close(fd);
// 	// fd1 = open("ft_test1.txt", O_RDWR | O_CREAT, 0777);
// 	// if (fd1 == -1)
// 	// 	return (1);
// 	// printf("fd1 = %d\n", fd1);
// 	// write(fd1, a, a_len);
// 	// close(fd1);
// 	return (0);
// }