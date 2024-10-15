/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 18:01:08 by mstencel      #+#    #+#                 */
/*   Updated: 2024/02/04 13:34:49 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
// #include <fcntl.h>
// int	main(void)
// {
// 	char	*a = "can you see me?";
// 	int		fd;

// 	fd = open("ft_test.txt", O_RDWR | O_CREAT, 0777);
// 	if (fd == -1)
// 		return (1);
// 	ft_putendl_fd(a, fd);
// 	printf("fd = %d\n", fd);
// 	close(fd);
// 	return (0);
// }