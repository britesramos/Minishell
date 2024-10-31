/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishellp.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 11:59:16 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/31 12:35:05 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLP_H
# define MINISHELLP_H

# include <stdbool.h>
# include "minishell.h"

typedef struct s_token t_token;

typedef enum e_tokens
{
	T_WORD,
	T_PIPE,
	T_REIN,
	T_REOUT,
	T_APPEND,
	T_HEREDOC,
	// T_EOF, ???
	T_ERROR,
}	t_token_t;

typedef struct s_token
{
	char		*str;
	int			lenght;
	t_token_t	type;
	t_token		*next;
}	t_token;

# endif
