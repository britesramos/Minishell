/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/18 20:43:22 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token *create_new_node(t_token_t type, char *str)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		error_exit("Memory allocation failed!", 1);
	node->str = ft_strdup(str);
	node->lenght = ft_strlen(str);
	node->type = type;
	node->next = NULL;
	return (node);
}

static void	create_token_list(t_token **token_list, char *str, t_token_t type)
{
	t_token *newnode;
	t_token *current;

	current = *token_list;
	newnode = create_new_node(type, str);
	if (*token_list == NULL)
		*token_list = newnode;
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

static void	heredoc_token(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 2)
		error_exit("Invalid input [Tokenization - HereDoc].", 1); //Check SEO.
	create_token_list(token_list, str, T_HEREDOC);
}

static void append_token(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 2)
		error_exit("Invalid input [Tokenization - Append].", 1); //Check SEO.
	create_token_list(token_list, str, T_APPEND);
}

static void	redirection_out(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 1)
		error_exit("Invalid input [Tokenization - Redirectin_out].", 1); //Check SEO.
	create_token_list(token_list, str, T_REOUT);
}

static void	redirection_in(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 1)
		error_exit("Invalid input [Tokenization - Redirection_in].", 1); //Check SEO.
	create_token_list(token_list, str, T_REIN);
}

static void free_token_list(t_token *token_list)
{
	while(token_list)
	{
		free (token_list);
		token_list = token_list->next;
	}
}

static void free_cmd_list(t_cmd *list)
{
	while(list)
	{
		free (list);
		list = list->pipe;
	}
}

static t_token *tokenization(t_data *data, t_token *token_list)
{
	char **line_array;
	int	i;

	i = 0;
	line_array = ft_split(data->line, ' '); //This doesnt work. Might not have spaces in between.
	while (line_array[i])
	{
		if (ft_strnstr(line_array[i], "<<", 2))
			heredoc_token(line_array[i], &token_list);
		else if(ft_strnstr(line_array[i], ">>", 2) != NULL)
			append_token(line_array[i], &token_list);
		else if(ft_strnstr(line_array[i], ">", 1))
			redirection_out(line_array[i], &token_list);
		else if(ft_strnstr(line_array[i], "<", 1))
			redirection_in(line_array[i], &token_list);
		else if(ft_strnstr(line_array[i], "|", 1))
			create_token_list(&token_list, line_array[i], T_PIPE);
		else
			create_token_list(&token_list, line_array[i], T_WORD);
		i++;
	}
	free_split(line_array);
	return (token_list);
}

static t_cmd *create_new_node_cmd()
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		error_exit("Memory allocation failed!", 1);
	node->cmd = NULL;
	// node->append = false;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->infile = NULL;
	node->outfile = NULL;
	node->pipe = NULL;
	
	return (node);
}

static char **ft_realloc(int number_of_times, char **old_array)
{
	char **new;
	int	i = 0;

	new = (char **)calloc(number_of_times, sizeof(char *));
	if(!new)
		error_exit("Memory calloc failed!\n", 1); //fix

	while (old_array[i])
	{
		new[i] = ft_strdup(old_array[i]);
		//Protect.
		i++;
	}
	while (i > 0)
	{
		free(old_array[i]);
		old_array[i] = NULL;
		i--;
	}
	free(old_array);
	old_array = NULL;
	return(new);
}

static void	parse_input2(t_data *data, t_token *token_list)
{
	t_token *current_token;
	t_cmd	*current_cmd;
	t_cmd	*newnode;
	int		i;
	int 	number_of_times_you_have_allocated;

	i = 0;
	number_of_times_you_have_allocated = 2;
	current_token = token_list;
	current_cmd = data->cmd_head;
	while(current_token)
	{
		newnode = create_new_node_cmd();
		if(current_cmd == NULL)
		{
			current_cmd = newnode;
			data->cmd_head = current_cmd;
		}
		else if(current_cmd != NULL)
		{
			while (current_cmd != NULL)
				current_cmd = current_cmd->pipe;
			current_cmd = newnode;
		}
		while(current_token && current_token->type != T_PIPE)
		{
			if (current_token->type == T_REIN)
			{
				current_token = current_token->next;
				// if(current_token->type == T_WORD) //Fix tokenization first.
				if (current_cmd->infile)
				{
					free(current_cmd->infile);
					close(current_cmd->fd_in);
				}
				current_cmd->fd_in = open(current_token->str, O_RDONLY);
				if (current_cmd->fd_in == -1)
				{
					error_exit("BAAAAAAAAAA!\n", 1);
				}
					//syntax error infile does not exist
				current_cmd->infile = ft_strdup(current_token->str);
				if(!current_cmd->infile)
					error_exit("Infile red allocation failed!\n", 1); //Free memory.
				// printf("RED IN: %s\n", current_cmd->infile);
			}
			else if (current_token->type == T_REOUT)
			{
				current_token = current_token->next;
				if (current_cmd->outfile)
				{
					free(current_cmd->outfile);
					close(current_cmd->fd_out);
				}
				current_cmd->fd_out = open(current_token->str, O_CREAT | O_TRUNC | O_RDWR);
				if (current_cmd->fd_out == -1)
					//do something
				current_cmd->outfile = ft_strdup(current_token->str);
				if(!current_cmd->outfile)
					error_exit("Outfile red allocation failed!\n", 1); //Free memory.
				// printf("RED OUT: %s\n", current_cmd->outfile);
			}
			else if (current_token->type == T_APPEND)
			{
				// current_cmd->append = true;
				current_token = current_token->next;
				if (current_cmd->outfile)
				{
					free(current_cmd->outfile);
					close(current_cmd->fd_out);
				}
				current_cmd->fd_out = open(current_token->str, O_CREAT | O_APPEND | O_RDWR);
				current_cmd->outfile = ft_strdup(current_token->str);
				if (current_cmd->fd_out == -1)
					//do something
				if(!current_cmd->outfile)
					error_exit("Outfile Append allocation failed!\n", 1); //Free memory.
				// printf("APPEND\n");
			}	
			else if (current_token->type == T_WORD)
			{
				// printf("HERE6!\n");
				if (current_cmd->cmd == NULL)
				{
					current_cmd->cmd = (char **)malloc(number_of_times_you_have_allocated * sizeof(char *));
				}
				if (number_of_times_you_have_allocated <= 0)
				{
					current_cmd->cmd = ft_realloc(2 + i, current_cmd->cmd);
					number_of_times_you_have_allocated = 2;
				}
				if (number_of_times_you_have_allocated > 0)
				{
					// printf("%i\n", i);
					current_cmd->cmd[i] = ft_strdup(current_token->str);
					// printf("current_cmd->cmd[%i]: %s\n", i, current_cmd->cmd[i]);
					i++;
					number_of_times_you_have_allocated--;
				}
				// current_token = current_token->next;
			}
			current_token = current_token->next;
		}
		if (current_token && current_token->type == T_PIPE)
			current_token = current_token->next;
		// printf("ANOTHER PIPE!\n");
	}
}

void	parse_input(t_data *data)
{
	t_token	*token_list;

	token_list = NULL;
	token_list = tokenization(data, token_list);

	// t_token *current = token_list;
	// while (current)
	// {
	// 	printf("%i\n", current->lenght);
	// 	printf("%s\n", current->str);
	// 	printf("%i\n\n\n", current->type);
	// 	current = current->next;
	// }
	parse_input2(data, token_list);
	t_cmd *current = data->cmd_head;
	while (current)
	{
		printf("This is cmd[0]: %s\n", current->cmd[0]);
		printf("This is cmd[1]: %s\n", current->cmd[1]);
		printf("This is cmd[2]: %s\n", current->cmd[2]);
		printf("This is cmd[3]: %s\n", current->cmd[3]);
		printf("This is fd_in: %i\n", current->fd_in);
		printf("This is fd_out: %i\n", current->fd_out);
		printf("This is infile: %s\n", current->infile);
		printf("This is outfile: %s\n", current->outfile);
		current = current->pipe;
	}
	free_cmd_list(data->cmd_head);
	free_token_list(token_list);
}
