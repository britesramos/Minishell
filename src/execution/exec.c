/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:28:52 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 19:22:13 by mstencel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr++ = '\0';
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	void	*ptr;

	i = 0;
	ptr = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb < 0 || size < 0)
		return (NULL);
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		i;

	i = 0;
	substr = NULL;
	if (s == NULL)
		return (0);
	if ((int)start > ft_strlen(s))
		return (ft_substr(s, 0, 0));
	if ((int)start + (int)len < ft_strlen(s))
		substr = malloc((len + 1) * sizeof(char));
	else
		substr = malloc((ft_strlen(s) - (int)start + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (len-- && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static int	ft_c_count(char *s, char c)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c && i != 0)
			count++;
		if (s[i + 1] == '\0' && s[i] != c)
			count++;
		i++;
		if (ft_strchr(s, c) == 0)
			return (count = 1);
	}
	return (count);
}

static int	ft_substrlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	ft_free(char **result, int j)
{
	if (result[j] == NULL)
	{
		while (j--)
			free (result[j]);
		free (result);
		return (0);
	}
	return (1);
}

static char	**ft_parsing(char *s, char c, char **result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && i == 0)
		{
			result[j] = ft_substr(s, 0, ft_substrlen(&s[i], c));
			if (ft_free(result, j) == 0)
				return (0);
			j++;
		}
		else if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			result[j] = ft_substr(s, i + 1, ft_substrlen(&s[i + 1], c));
			if (ft_free(result, j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (result);
}

char	**ft_split(char *s, char c)
{
	int		c_count;
	char	**result;

	if (ft_strlen(s) == 0)
		c_count = 0;
	else
		c_count = ft_c_count(s, c);
	result = ft_calloc ((c_count + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (ft_parsing(s, c, result));
}

void	exec(t_data *data)
{
	char	**args;
	
	args = ft_split(data->line, ' ');
	ft_t_check(args, data->envp_head);
	int i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}
