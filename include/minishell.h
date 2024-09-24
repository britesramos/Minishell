/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:16:41 by sramos            #+#    #+#             */
/*   Updated: 2024/09/24 10:47:46 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "minishellp.h"
// #include "minishelle.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
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
/*If add any new value, do not forget to init in init.c - init_main_struct*/
typedef struct s_data
{
	char *line; /*Line from Readline function - user input from the terminal. - to be parsed*/
	t_cmd *cmd_head;
	t_cmd *cmd_current;
}	t_data;

/*Initialize main struct t_data data.*/
void	init_main_struct(t_data *data);

/*Parsing input*/
void	parsing(t_data *data);

#endif