/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishellp.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:16 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/15 15:40:25 by sramos        ########   odam.nl         */
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

# endif
