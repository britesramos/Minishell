/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 12:16:41 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/25 00:23:44 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishellp.h"
# include "minishelle.h"
# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
 
/*Nodes for linked list with parsed input for execution.*/
typedef struct s_cmd
{
	char	**cmd; /*Commands arguments and flags*/
	// bool	flag;
	// bool	append;
	int		fd_in; /*STIN*/
	int		fd_out; /*STOUT*/
	char	*infile; /*Init as NULL if not exists. Or name of file.*/
	char	*outfile; /*Init as NULL if not exists. Or name of file.*/
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
	int		nbr_pipes;
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_envp	*envp_head; /*Pointer to linked list header | Parsed envp*/
}	t_data;

/*Initialize main struct t_data data.*/
void	init_main_struct(t_data *data);


/*-----------------------------------PARSING-----------------------------------*/
/*Parsing input*/
void	parsing(t_data *data, char **envp);
void	parse_input(t_data *data);

/*Tokenization*/
void tokenization(t_data *data, t_token *token_list);
int	ms_isspace(char c);
t_token *create_new_node(t_data *data, t_token_t type, char *str);
void	create_token_list(t_data *data, t_token **token_list, char *str, t_token_t type);

/*Invalid input checker*/
int	input_checker(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Parsing_utils*/
int	is_space(char c);

/*Invalid input checker*/
void	invalid_input(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Error handling and exit error std.*/
int	error_exit(t_data *data, char *str, int type);

/*-----------------------------------PARSING-----------------------------------*/

/*Ending program and clean up.*/
void	clean_up(t_data *data);
void	free_split(char **array);

// EXECUTION

// headers for external functions
// getcwd(char *buf, size_t size) -> unistd.h
// PATH_MAX -> limits.h

# include <unistd.h>
// # include <linux/limits.h> //Uncoment back! Not recognize by windows.
# include <errno.h>

void	exec(t_data *data);
// tokens
// void	line_tok(char *line);
int	ft_built_in_check(char **cmd, t_data *data);

// built-in funtions:
int		ft_echo(char **cmd, t_data *data);
int		ft_pwd(char **cmd, t_data *data);
int		ft_exit(char **cmd, t_data *data);
void	ft_cd(char **cmd, t_data *data);

#endif