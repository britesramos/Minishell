/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 16:07:24 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/04 13:32:56 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
// #include <fcntl.h>
// int	main(void)
// {
	// char	*a = "Here is my first line \n and here is my second one... \n
	// let's see if it works \n";
// 	int		fd;
// 	// int		fd1;
// 	// size_t	a_len = ft_strlen(a);

// 	fd = open("ft_test.txt", O_RDWR | O_CREAT, 0777);
// 	if (fd == -1)
// 		return (1);
// 	ft_putstr_fd(a, fd);
// 	printf("fd = %d\n", fd);
// 	close(fd);
// 	// fd1 = open("ft_test1.txt", O_RDWR | O_CREAT, 0777);
// 	// if (fd1 == -1)
// 	// 	return (1);
// 	// printf("fd1 = %d\n", fd1);
// 	// write(fd1, a, a_len);
// 	// close(fd1);
// 	return (0);
// }