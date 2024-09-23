/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:16 by sramos            #+#    #+#             */
/*   Updated: 2024/09/23 18:41:15 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLP_H
# define MINISHELLP_H

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
