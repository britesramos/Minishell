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


/*Fix and Replace this with ft_isalnum for the tokenization. Bash accept file names that include _ = - etc.*/
// int	ms_isword(char c)
// {
// 	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
// }

void free_token_list(t_token *token_list)
{
	t_token *to_free;
	to_free = token_list;
	while(to_free)
	{
		free(to_free->str);
		to_free->str = NULL;
		to_free->type = 0;
		token_list = token_list->next;
		free (to_free);
		to_free = token_list;
	}
}

t_token *create_new_node(t_data *data, t_token_t type, char *str)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		error_exit(data, NULL, "Memory allocation failed!", 1);
	node->str = ft_strdup(str);
	node->lenght = ft_strlen(str); //I dont think we need this.
	node->type = type;
	node->next = NULL;
	return (node);
}

void	create_token_list(t_data *data, t_token **token_list, char *str, t_token_t type)
{
	t_token *newnode;
	t_token *current;

	current = *token_list;
	newnode = create_new_node(data, type, str);
	if (*token_list == NULL)
		*token_list = newnode;
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}
