/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/22 10:46:36 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 12:52:08 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = "";
	newstr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!newstr)
		return (free((char *)s2), NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static char	*read_file(int fd, char *str)
{
	ssize_t	b_num;
	char	*buff;
	char	*temp;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(str), NULL);
	b_num = 1;
	while (b_num != 0 && !ft_strchr(str, '\n'))
	{
		b_num = read(fd, buff, BUFFER_SIZE);
		if (b_num < 0)
			return (free(str), free(buff), NULL);
		buff[b_num] = '\0';
		if (b_num == 0)
			break ;
		temp = ft_gnl_strjoin(str, buff);
		if (!temp)
			return (free(str), NULL);
		free(str);
		str = temp;
	}
	free(buff);
	return (str);
}

static char	*read_l(char *str)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = str[i++];
	line[j] = '\0';
	if (*line == '\0')
		return (free(line), NULL);
	return (line);
}

static char	*store_r(char *str, int str_len)
{
	char	*rest;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	rest = ft_calloc(str_len - i + 1, sizeof(char));
	if (!rest)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	j = 0;
	while (str[i] != '\0')
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	str = NULL;
	return (rest);
}

/// @param flag should equal to 1 upon an error (frees the *str)
char	*get_next_line(int fd, int flag)
{
	static char	*str = NULL;
	char		*line;
	int			str_len;

	if (flag == 1)
		return (ft_free(&str), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	line = read_l(str);
	if (!line)
		return (ft_free(&str), NULL);
	str = store_r(str, str_len);
	if (!str)
		return (ft_free(&line), NULL);
	return (line);
}
