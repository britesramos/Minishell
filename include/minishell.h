/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 12:16:41 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/17 13:34:27 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "minishellp.h"
#include "minishelle.h"
#include "../libft/libft.h"

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
	int append;
	
	int	fd_in;
	int	fd_out;
	// char *infile; /*int*/ /*Opening fds should be done in execution.*/
	// char *outfile; /*int*/
	struct s_cmd *pipe; /*Pointer to the next node*/
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
	char	*line; /*Line from Readline function - user input from the terminal. - to be parsed*/
	int		exit_code; 
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_envp	*envp_head; /*Pointer to linked list header | Parsed envp*/
}	t_data;

/*Initialize main struct t_data data.*/
void	init_main_struct(t_data *data);

/*Parsing input*/
void	parsing(t_data *data, char **envp);
/*Invalid input checker*/
void	invalid_input(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Ending program and clean up.*/
void	clean_up(t_data *data);

// EXECUTION

// headers for external functions
# include <errno.h>

// for PATH_MAX
# include <linux/limits.h>

// for getcwd()
# include <unistd.h>

// for the opendir()
# include <sys/types.h>
# include <dirent.h>

// void	exec(t_data *data);
void	exec(t_data *data);
// tokens
// void	line_tok(char *line);
int	ft_built_in_check(char **cmd, t_data *data);

// built-in funtions:
void	ft_cd(char **cmd, t_data *data);
void	ft_echo(char **cmd, t_data *data);
void	ft_env(char **cmd, t_data *data);
int		ft_exit(char **cmd, t_data *data);
void	ft_pwd(char **argv, t_data *data);



//envp utils
char	*find_value(t_data *data, char *key);
void	replace_value(t_data *data, char *key, char *new_value);


#endif