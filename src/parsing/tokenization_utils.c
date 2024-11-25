/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenization.utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 21:17:13 by anonymous     #+#    #+#                 */
/*   Updated: 2024/10/24 21:17:13 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_isspace(char c)
{
	return (c == ' ' || (c >= '\b' && c <= '\v'));
}

int	ms_isword(char c)
{
	return (c != '>' && c != '<' && c != '|' && c != '\0');
}

void	free_token_list(t_token *token_list)
{
	t_token	*to_free;

	to_free = token_list;
	while (to_free)
	{
		free(to_free->str);
		to_free->str = NULL;
		to_free->type = 0;
		token_list = token_list->next;
		free (to_free);
		to_free = NULL;
		to_free = token_list;
	}
}

t_token	*create_new_node(t_data *data, t_token_t type, char *str)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		error_exit(data, NULL, "Memory allocation failed!", 1);
	node->str = ft_strdup(str);
	node->lenght = ft_strlen(str);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	create_list(t_data *data, t_token **t_list, char *str, t_token_t type)
{
	t_token	*newnode;
	t_token	*current;

	current = *t_list;
	newnode = create_new_node(data, type, str);
	if (*t_list == NULL)
		*t_list = newnode;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}
