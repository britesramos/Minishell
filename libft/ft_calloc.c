/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 10:44:48 by mstencel      #+#    #+#                 */
/*   Updated: 2023/11/16 11:51:39 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;	

	ptr = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((nmemb * size) / nmemb != size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}
// int	main(void)
// {
// 	void * p = ft_calloc(2, 2);
// 	char e[] = {0, 0, 0, 0};
// 	printf("%d\n", (!memcmp(p, e, 4)));
// 	return (0);
// }
// #include <stdint.h>
// int	main(void)
// {
// 	int	n = 20;
// 	int	i = 0;
// 	int *ft_allocation = ft_calloc(n, sizeof(int));
// 	// int *ft_allocation = ft_calloc(SIZE_MAX, 2);

// 	// int	*allocation = (int *)calloc(n, sizeof(int));
// 	// int *allocation = calloc(SIZE_MAX, 2);
// 	// printf("Original function\n");
// 	// printf("%u\n", (unsigned int)(uintptr_t)allocation);
// 	// printf("%u\n", (unsigned int)(uintptr_t)allocation + n - 1);
// 	// printf("%p\n", allocation);
// 	// printf("%p\n", allocation + n - 1);
// 	// if (!allocation)
// 	// 	printf("Error, memory not allocated");

// 	// while(i < n)
// 	// {
// 	// 	printf("%d: %d| \n", i + 1, allocation[i]);
// 	// 	i++;
// 	// }	
// 	// free(allocation);

// 	printf("My function\n");
// 	printf("%u\n", (unsigned int)(uintptr_t)ft_allocation);
// 	printf("%u\n", (unsigned int)(uintptr_t)ft_allocation + n - 1);
// 	printf("pointer:%p\n", ft_allocation);
// 	printf("pointer:%p\n", ft_allocation + n - 1);
// 	if (!ft_allocation)
// 		printf("Error, memory not allocated");
// 	while(n--)
// 	{
// 		printf("%d \n", ft_allocation[i]);
// 		i++;
// 	}
// 	free(ft_allocation);
// 	return (0);
// }

// needs #include <stdint.h> for uintptr_t
// uintptr_t is an unsigned integer type that is capable
//  of storing a data pointer
// (whether it can hold a function pointer is unspecified). 
// Which typically means that it's the same size as a pointer.