/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:16 by sramos            #+#    #+#             */
/*   Updated: 2024/09/26 14:43:09 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLP_H
# define MINISHELLP_H

# include <stdbool.h>
# include "minishell.h"

typedef enum e_tokens
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REIN,
    TOKEN_REOUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_EOF,
    // TOKEN_ERROR, ???
}   t_token_t;

typedef struct s_token
{
    char    *start;
    int     lenght;
    t_token_t type;
}   t_token;

/*Parsing_utils*/
int	ft_strlen(char *str);
int	is_space(char c);

/*Invalid input checker*/
void	invalid_input(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Error handling and exit error std.*/
void    error_exit(char *str, int seo);

# endif
