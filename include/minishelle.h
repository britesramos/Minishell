/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishelle.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 11:12:59 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 08:34:51 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLE_H
# define MINISHELLE_H

# include "minishell.h"

# define PIPE_READ 0
# define PIPE_WRITE 1


typedef struct s_ex
{
	pid_t	pid;
	int		current_pipe;
	int		p_fd[2];
}	t_ex;



#endif
