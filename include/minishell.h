/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:16:41 by sramos            #+#    #+#             */
/*   Updated: 2024/09/26 19:16:32 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishellp.h"
# include "minishelle.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*Nodes for linked list with parsed input for execution.*/
typedef struct s_cmd
{
	char **cmd;
	// char **argv;
	char **here_doc;
	struct s_cmd *pipe; /*Pointer to the next node*/
	// char *infile; /*int*/ /*Opening fds should be done in execution.*/
	// char *outfile; /*int*/
}	t_cmd;

/*Parsed env node (linked list)*/
typedef struct s_envp
{
	char *key;
	char *value;
	struct s_envp *next;
}	t_envp;

/*Main struct*/
/*If add any new value, do not forget to init in init.c - init_main_struct*/
typedef struct s_data
{
	char *line; /*Line from Readline function - user input from the terminal. - to be parsed*/
	t_cmd *cmd_head;
	t_cmd *cmd_current;
	t_envp *envp_head; /*Pointer to linked list header | Parsed envp*/
}	t_data;

/*Initialize main struct t_data data.*/
void	init_main_struct(t_data *data);


/*-----------------------------------PARSING-----------------------------------*/
/*Parsing input*/
void	parsing(t_data *data, char **envp);

/*Parsing_utils*/
int	ft_strlen(char *str);
int	is_space(char c);

/*Invalid input checker*/
void	invalid_input(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Error handling and exit error std.*/
void    error_exit(char *str, int seo);
/*-----------------------------------PARSING-----------------------------------*/

/*Ending program and clean up.*/
void	clean_up(t_data *data);

#endif