/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:16:41 by sramos            #+#    #+#             */
/*   Updated: 2024/09/23 18:41:15 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "minishellp.h"
// #include "minishelle.h"

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*Nodes for linked list with parsed input for execution.*/
typedef struct s_cmd
{
	char **cmd;
	char *infile;
	char *outfile;
	char **here_doc;
	struct s_cmd *pipe;
}	t_cmd;

/*Main struct*/
typedef struct s_data
{
	char *line; /*Line from Readline function - user input from the terminal.*/
	t_cmd *cmd_head;
	t_cmd *cmd_current;
}	t_data;

void	parsing(t_data *data);

#endif