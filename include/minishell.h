/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 12:16:41 by sramos        #+#    #+#                 */
/*   Updated: 2024/12/02 09:14:06 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

/*for execution*/
// for errno
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
//for the stat() ->checking if path is a directory
# include <sys/stat.h>

/*Tokenization structs*/
typedef struct s_token	t_token;

typedef enum e_tokens
{
	T_WORD,
	T_PIPE,
	T_REIN,
	T_REOUT,
	T_APPEND,
	T_HEREDOC,
	T_ERROR,
}	t_token_t;

typedef struct s_token
{
	char		*str;
	int			lenght;
	t_token_t	type;
	t_token		*next;
}	t_token;

/*Nodes for linked list with parsed input for execution.*/
typedef struct s_cmd
{
	char			**cmd; /*Commands, arguments and flags*/
	bool			heredoc;
	int				fd_in; /*STIN*/
	int				fd_out; /*STOUT*/
	char			*infile; /*Init as NULL if not exists. Or name of file.*/
	char			*outfile; /*Init as NULL if not exists. Or name of file.*/
	char			*error;
	bool			invalid_fd_in;
	bool			invalid_fd_out;
	struct s_cmd	*pipe; /*Pointer to the next node*/
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
	char	*line; /*from Readline function-user input from the terminal*/
	char	*hd_line;
	char	**envp;
	bool	invalid_fd;
	int		exit_code;
	int		nbr_pipes;
	int		std[2];
	t_token	*token_list;
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_envp	*envp_head; /*Pointer to linked list header | Parsed envp*/
}	t_data;

//DELETE ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	print_cmd_list(t_data *data);
void	print_token_list(t_token *token_list);
//DELETE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
void	expand_path_digit_alloc(t_data *data, char *temp, char *leftover);
void	concatenate_newline(t_data *data, char *value, char *leftover);
char	*convert_exit_code(t_data *data);
void	alloc_newline(t_data *data, char *temp, char *value, char *leftover);
char	*expansion_heredoc(t_data *data);

/*-----------------------------------PARSING-----------------------------*/

/*Parsing input*/
void	parsing(t_data *data);
int		parse_input(t_data *data, t_token *token_list);
int		parse_input_help(t_data *data, t_token **c_t, t_cmd **c_cmd, int *i);
t_token	*p_redirections(t_token *current_t, t_cmd *c_cmd, t_data *data);
t_token	*p_rein(t_token *current_t, t_cmd *current_cmd, t_data *data);
t_token	*p_reout(t_token *current_t, t_cmd *c_cmd, t_data *data);
t_token	*p_append(t_token *current_t, t_cmd *current_cmd, t_data *data);
t_token	*p_pipe(t_token *current_t, t_data *data);
int		p_word(t_token *current_t, t_cmd *current_c, t_data *data, int i);

/*Tokenization*/
void	tokenization(t_data *data);
int		ms_isspace(char c);
char	*token_word_remove_extra_quotes(char *new, t_data *data);
char	*token_word_remove_extra_spaces(char *new, t_data *data);
int		len_result(t_data *data, int start);
t_token	*create_new_node(t_data *data, t_token_t type, char *str);
void	create_list(t_data *data, t_token **t_list, char *str, t_token_t type);
void	free_token_list(t_token *token_list);

/*HEREDOC parsing*/
t_token	*p_heredoc(t_token *current_token, t_cmd *current_cmd, t_data *data);

/*Invalid input checker*/
int		start_with_pipe(char *str);
int		multiple_pipes(char *str);
int		redin_to_pipe(char *str);
int		missing_closing_q_marks(char *str);
int		multiple_redirections(char *str);
int		unexpected_new_line(char *str);
int		input_checker(t_data *data, char *line);
int		error_input_checker(t_data *data, char *str, int type);
int		error_unexpected_token(t_data *data, char *str, int type);

int		pipe_at_end(char *line);

/*Parsing envp*/
void	parse_envp(t_data *data, char **envp);

/*Parsing_utils*/
int		is_space(char c);
int		ms_isword(char c);
int		only_spaces(t_data *data);

/*Parsing input utils*/
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
int		error_exit(t_data *data, char *file, char *str, int type);
int		error_exit_system(t_data *data, char *str, t_cmd *cmd, int type);

/*-----------------------------------PARSING------------------------------*/

/*Ending program and clean up.*/
void	clean_up(t_data *data);
void	clean_up_parse_input(t_data *data, t_token *token_list);
void	clean_up_token_list(t_token	*token_list);
void	free_split(char **array);
void	free_envp(t_envp *envp_head);

//COMMON FUNCTIONS
t_envp	*create_node_envp(t_data *data, char *envp);

# define READ 0
# define WRITE 1

# define IN 0
# define OUT 1

# define INTERACTIVE 1
# define NONINTERACTIVE 2
# define HEREDOC 3

# define NO_PATH 0
# define NO_COMMAND 1
# define IS_DIR 2
# define NO_PERM 3

/*-----------------------------------EXECUTION------------------------------*/

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
int		ft_export_init_check(char *cmd);
void	ft_export_error(char *cmd, t_data *data);
void	ft_print_export(t_data *data, int fd);
void	ft_pwd(char **cmd, t_data *data, int fd);
void	ft_unset(char **cmd, t_data *data);

// pipes functions:
void	single_cmd(t_data *data);
int		mltpl_cmd(t_data *data);
void	get_path_error(t_data *data, char **path);
void	path_error(t_data *data, char *cmd, int flag);
void	cmd_error(char *cmd, char *str, t_data *data);
void	cmd_extra_error(char *cmd, char *str, char *str1, t_data *data);
void	mini_error(char *cmd, char *str, t_data *data);

// fd_utils
void	child_fd_handling(t_data *data, t_ex *ex);

//envp utils
void	add_node(t_data *data, char *cmd, t_envp **env);
char	*init_key_export(char *cmd, t_data *data);
char	*init_value_export(char *cmd, t_data *data);
char	*init_replace_value_export(char *cmd, t_data *data);
char	*find_value(t_data *data, char *key);
void	replace_value(t_data *data, char *key, char *new_value);

//signals
void	ms_signals(int process);

//clean-up
void	close_fd(int *fd);
int		bye(t_data *data);
#endif