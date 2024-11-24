/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 12:16:41 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/24 13:23:43 by mstencel      ########   odam.nl         */
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
# include <linux/limits.h>

/*Nodes for linked list with parsed input for execution.*/
typedef struct s_cmd
{
	char	**cmd; /*Commands, arguments and flags*/
	bool	heredoc;
	// char	*hd_delimiter;
	int		fd_in; /*STIN*/
	int		fd_out; /*STOUT*/
	char	*infile; /*Init as NULL if not exists. Or name of file.*/
	char	*outfile; /*Init as NULL if not exists. Or name of file.*/
	struct s_cmd *pipe; /*Pointer to the next node*/
}	t_cmd;

/*Parsed env node (linked list)*/
typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

/*Main struct*/
/*If add any new value, do not forget to init in init.c - init_main_struct*/
typedef struct s_data
{
	char	*line; /*Line from Readline function - user input from the terminal. - to be parsed*/
	char	*hd_line;
	char	**envp;
	int		exit_code;
	int		nbr_pipes;
	int		std[2];
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_envp	*envp_head; /*Pointer to linked list header | Parsed envp*/
}	t_data;

typedef struct s_ex
{
	pid_t	pid;
	int		p_fd[2];
	int		i;
	int		pid_store[1024];
	int		fd_in;
	int		status;
}	t_ex;

/*Initialize main struct t_data data.*/
void	init_main_struct(t_data *data, char **envp);

/*EXPANSIONS*/
void	expansion(t_data *data);
int		expansion_quotes(t_data *data, int i);
void	concatenate_newline(t_data *data, char *value, char *leftover);
char	*convert_exit_code(t_data *data);
void	alloc_newline(t_data *data, char *temp, char *value, char *leftover);
char 	*expansion_heredoc(t_data *data, char *heredoc_line);

/*-----------------------------------PARSING-----------------------------------*/

/*Parsing input*/
void	parsing(t_data *data, char **envp);
int		parse_input(t_data *data, t_token *token_list);
void	create_add_node(t_data *data, t_cmd *current_cmd);
t_token	*p_redirections(t_token *current_t, t_cmd *c_cmd, t_data *data);
t_token	*p_rein(t_token *current_t, t_cmd *current_cmd, t_data *data);
t_token	*p_reout(t_token *current_t, t_cmd *c_cmd, t_data *data);
t_token	*p_append(t_token *current_t, t_cmd *current_cmd, t_data *data);
t_token	*p_pipe(t_token *current_t, t_data *data);


/*Tokenization*/
t_token *tokenization(t_data *data, t_token *token_list);
int		ms_isspace(char c);
char	*token_word_remove_extra_quotes(char *new, t_data *data);
char	*token_word_remove_extra_spaces(char *new, t_data *data);
t_token *create_new_node(t_data *data, t_token_t type, char *str);
void	create_t_list(t_data *data, t_token **token_list, char *str, t_token_t type);
void 	free_token_list(t_token *token_list);

/*HEREDOC parsing*/
t_token	*p_heredoc(t_token *current_token, t_cmd *current_cmd, t_data *data);

/*Invalid input checker*/
int		start_with_pipe(char *str);
int		multiple_pipes(char *str);
int		missing_closing_q_marks(char *str);
int		multiple_redirection(char *str);
int		lonely_redirection(char *str);
int		input_checker(t_data *data);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Parsing_utils*/
int		is_space(char c);
int		ms_isword(char c);
int		only_spaces(t_data *data);

/*Parsing input utils*/
void 	free_null(void **input);
void	free_null_2d_array(char **str);
void	free_null_array(char *str);
void	free_close_fd(char *file, int fd);
void	free_cmd_list(t_cmd *list);
t_cmd	*create_new_node_cmd(t_data *data);
void	add_new_node(t_cmd **head, t_cmd *newnode, t_cmd **current_cmd);
char	**ft_realloc(t_data *data, int number_of_times, char **old_array);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Error handling and exit error std.*/
int	error_exit(t_data *data, char *file, char *str, int type);
int	error_exit_system(t_data *data, char *str, int type);


/*-----------------------------------PARSING-----------------------------------*/

/*Ending program and clean up.*/
void	clean_up(t_data *data);
void	free_split(char **array);
void	free_envp(t_envp *envp_head);




//COMMON FUNCTIONS
t_envp	*create_node_envp(t_data *data, char *envp);

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

//for waitpid()
# include <sys/types.h>
# include <sys/wait.h>

//for signals
# include <signal.h>

#define READ 0
#define WRITE 1

#define IN 0
#define OUT 1

#define INTERACTIVE 1
#define NONINTERACTIVE 2
#define HEREDOC 3

#define NO_PATH 0
#define NO_COMMAND 1

int		exec(t_data *data);
int		ft_builtin_manager(t_data *data, int fd);

// built-in funtions:
void	ft_cd(char **cmd, t_data *data);
void	cd_errno_error(t_data *data, char *path);
char	*ft_getcdw_err(t_data *data);
char	*ft_getcwd_parent_err(t_data *data);
void	ft_echo(char **cmd, t_data *data, int fd);
void	ft_env(char **cmd, t_data *data, int fd);
int		ft_exit(char **cmd, t_data *data);
void	ft_export(char **cmd, t_data *data, int fd);
void	ft_export_error(char *cmd, t_data *data);
void	ft_print_export(t_data *data, int fd);
void	ft_pwd(char **cmd, t_data *data, int fd);
void	ft_unset(char **cmd, t_data *data);

// pipes functions:
void	single_cmd(t_data *data);
int		mltpl_cmd(t_data *data);
void	get_path_error(t_data *data, char **path);

// fd_utils
int		child_fd_handling(t_data *data, t_ex *ex);

//envp utils
void	add_node(t_data *data, char *cmd, t_envp **env);
char	*init_key_export(char *cmd, t_data *data);
char	*init_value_export(char *cmd, t_data *data);
char	*find_value(t_data *data, char *key);
void	replace_value(t_data *data, char *key, char *new_value);


void	ms_signals(int process);

void	close_fd(int *fd);
int		bye(t_data *data);
#endif