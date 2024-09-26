/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelle.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstencel <mstencel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:12:59 by mstencel          #+#    #+#             */
/*   Updated: 2024/09/26 12:15:42 by mstencel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLE_H
# define MINISHELLE_H

// # include "minishell.h"

// to be deleted!!!
#include <stdio.h>


// headers for external functions
// getcwd(char *buf, size_t size) -> unistd.h
// PATH_MAX -> limits.h

# include <unistd.h>
# include <linux/limits.h>

typedef struct s_tokens
{
	size_t			length;
	char			*start;
	char			*name;
	// int			type;
	struct s_tok	*next;
} t_tok;

// tokens
// void	line_tok(char *line);
int		ft_t_check(char **argv);

// built-in funtions:
void	ft_echo(char **argv);
int	ft_pwd(char **argv);

#endif
