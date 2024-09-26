/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:38:59 by sramos            #+#    #+#             */
/*   Updated: 2024/09/26 14:40:31 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	*init_key(char *envp)
{
	int	i;
	int	key_len;
	char *key;

	i = 0;
	key_len = 0;
	key = NULL;
	while(envp[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	if(!key)
		error_exit("Memory allocation failed! [key | env parsing]", 1);
	while(i < key_len)
	{
		key[i] = envp[i];
		i++;
	}
	return (key);
}

static char	*init_value(char *envp)
{
	int		i;
	int		key_len;
	char	*value;

	i = 0;
	key_len = 0;
	value = NULL;
	while (envp[key_len] != '=')
		key_len++;
	value = malloc(strlen(envp) - key_len + 1);
	if(!value)
		error_exit("Memory allocation failed! [value | env parsing]", 1);
	while ((i + key_len) < ft_strlen(envp))
	{
		value[i] = envp[key_len + i];
		i++;
	}
	return(value);
}

static t_envp	*create_node_envp(char *envp)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		error_exit("Memory allocation failed! [Node creation | env parsing]\n", 1);
	node->key = init_key(envp);
	node->value = init_value(envp);
	node->next = NULL;
	return (node);
}

void	parse_envp(t_data *data, char **envp)
{
	int i;
	t_envp	*current;
	t_envp	*new_node;

	i = 0;
	current = NULL;
	new_node = NULL;
	while(envp[i])
	{
		new_node = create_node_envp(envp[i]);
		if (data->envp_head == NULL)
		{
			data->envp_head = new_node;
			current = data->envp_head;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
}
