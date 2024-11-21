/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/22 10:46:36 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/21 15:17:02 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_extline(char *buffer)
{
	int		linelen;
	char	*line;
	int		i;

	linelen = 0;
	i = 0;
	while (buffer[linelen] != '\n' && buffer[linelen] != '\0')
		linelen++;
	if (buffer[linelen] == '\n')
		linelen++;
	line = malloc(linelen + 1 * sizeof(char));
	if (!line)
		return (NULL);
	linelen = 0;
	while (buffer[linelen] != '\n' && buffer[linelen] != '\0')
		line[linelen++] = buffer[i++];
	if (buffer[linelen] == '\n')
		line[linelen++] = buffer[i++];
	line[linelen] = '\0';
	if (*line == '\0')
		return (ft_free(&line), NULL);
	return (line);
}

static char	*ft_leftovers(char *buffer, char *line)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = "";
	temp = ft_strjoin(temp, buffer);
	ft_free(&buffer);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	if ((ft_strlen(temp) - ft_strlen(line)) == 0)
	{
		ft_free(&temp);
		return (NULL);
	}
	buffer = malloc(ft_strlen(temp) - ft_strlen(line) + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	while (temp[i])
	{
		buffer[j] = temp [i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	ft_free(&temp);
	return (buffer);
}

static char	*ft_read(int fd, char *buffer)
{
	int		bytes_read;
	char	*pot;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		pot = malloc(sizeof (char) * BUFFER_SIZE + 1);
		if (!pot)
			return (NULL);
		bytes_read = read(fd, pot, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			ft_free(&pot);
			break ;
		}
		if (bytes_read < 0)
			return (ft_free(&pot), ft_free(&buffer), NULL);
		pot[bytes_read] = '\0';
		temp = ft_strjoin(buffer, pot);
		ft_free(&buffer);
		buffer = temp;
		ft_free(&pot);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer || !*buffer)
		return (ft_free(&buffer), NULL);
	line = ft_extline(buffer);
	buffer = ft_leftovers(buffer, line);
	return (line);
}
