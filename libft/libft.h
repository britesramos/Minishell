/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:12:13 by mstencel      #+#    #+#                 */
/*   Updated: 2024/07/26 09:20:46 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

//libft
# include <stdlib.h>
# include <unistd.h>

//ft_printf
// # include <unistd.h>
# include <stdarg.h>

//get_next_line
// # include <stdlib.h>
// # include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_free(char **str);

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

//ft_printf
int		ft_printf(const char *format, ...);
int		ft_putchar(char a);
int		ft_putstr(char *s);
int		ft_putnum(int n);
int		ft_u_int(unsigned int number);
int		ft_hex(unsigned int value, int base);
int		ft_ptr_help(size_t value);
int		ft_pt_address(char *ptr);

//get_next_line
char	*get_next_line(int fd, int flag);

#endif