/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 18:01:08 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/28 10:55:13 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*str;
	int		len;

	str = ft_strjoin(s, "\n");
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	ft_free_string(&str);
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