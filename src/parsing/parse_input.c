/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 18:23:26 by sramos        #+#    #+#                 */
/*   Updated: 2024/10/17 16:29:20 by sramos        ########   odam.nl         */
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

static void append(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 2)
		error_exit("Invalid input [Tokenization - Append].", 1); //Check SEO.
	create_token_list(token_list, str, T_APPEND);
}

static void	redirection_out(char *str, t_token **token_list)
{
	if (ft_strlen(str) != 1)
		error_exit("Invalid input [Tokenization - Append].", 1); //Check SEO.
	create_token_list(token_list, str, T_REOUT);
}

static void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
}

static void free_token_list(t_token *token_list)
{
	while(token_list)
	{
		free (token_list);
		token_list = token_list->next;
	}
}

static t_token *tokenization(t_data *data, t_token *token_list)
{
	char **line_array;
	int	i;

	i = 0;
	line_array = ft_split(data->line, ' ');
	while (line_array[i])
	{
		// if(ft_strnstr(line_array[i], '<<', 2) && (ft_strlen(line_array[i]) == 2))
			//HEREDOC.
		// printf("This is line_array[%i]: %s\n", i, line_array[i]);
		// printf("This is line_array len: %zu\n", ft_strlen(line_array[i]));
		if(ft_strnstr(line_array[i], ">>", 2) != NULL)
			append(line_array[i], &token_list);
		else if(ft_strnstr(line_array[i], ">", 1))
			redirection_out(line_array[i], &token_list);
		// else if(ft_strnstr(line_array[i], '<', 1) && (ft_strlen(line_array[i]) == 1))
		// 	redirection_in(line_array[i], token_list);
		// else
		// 	word(line_array[i], token_list);
		i++;
	}
	free_split(line_array);
	return (token_list);
}

void	parse_input(t_data *data)
{
	t_token	*token_list;

	token_list = NULL;
	token_list = tokenization(data, token_list);

	t_token *current = token_list;
	while (current)
	{
		printf("%i\n", current->lenght);
		printf("%s\n", current->str);
		printf("%i\n\n\n", current->type);
		current = current->next;
	}
	
	//4 - Parsed input
	free_token_list(token_list);
}
