/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 11:04:56 by mstencel      #+#    #+#                 */
/*   Updated: 2024/07/26 09:08:08 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_substrlen(char const *s, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	**free_mem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**ft_change(char const *s, char c, char **result, int count)
{
	int	n;
	int	sublen;

	n = 0;
	while (*s && n < count)
	{
		while (*s == c)
			s++;
		if (*s != c)
		{
			sublen = ft_substrlen(s, c);
			result[n] = ft_substr(s, 0, sublen);
			if (!result[n])
			{
				free_mem(result);
				return (NULL);
			}
			s += sublen;
			n++;
		}
	}
	result[n] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;

	count = ft_count(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	result = ft_change(s, c, result, count);
	if (!result)
		return (NULL);
	return (result);
}

// int	main(void)
// {
// 	char	**array;
// 	// char	*str = "  tripouille  42  ";
// 	// char	*str = "qwe";
// 	// char	*str = "olol                     ";
// 	char	del = ' ';
// 	// char	*str = "ggggggggggg";
// 	// char	del = 'g';
// 	char	*str = "";
// 	// char	del = 'z';
// 	int		i = 0;

// 	array = ft_split(str, del);
// 	while(array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }

// int	main(void)
// {
// 	char	**array;
// 	char	*str = ",,,yi,er,,,,san,si,wu,liu,qi,ba,jiu,shi,,";
// 	char	del = ',';
// 	int		i = 0;

// 	array = ft_split(str, del);
// 	while(array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }
