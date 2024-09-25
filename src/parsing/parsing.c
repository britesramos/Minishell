/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sramos <sramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:18 by sramos            #+#    #+#             */
/*   Updated: 2024/09/25 18:47:07 by sramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishellp.h"

static int	start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while(is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

static int	multiple_pipes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '|' && str[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

static void	invalid_input(t_data *data)
{
	if (start_with_pipe(data->line) == 1 || multiple_pipes(data->line) == 1)
		error_exit("minishell: syntax error near unexpected token `||'", 2);
	/*This should not exit on error, it should wait for the final quotation mark.*/
	// if (missing_q_marks(data->line) == 1)
	// 	error_exit();
}

static t_envp	*create_node(char *envp)
{
	int	i;
	int	j;
	t_envp	*node;
	char *key;
	char *value;
	
	key = NULL;
	value = NULL;
	i = 0;
	j = 0;
	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		error_exit("Memory allocation failed! [Node creation | envp parsing]\n", 1);
	printf("envp: %s\n", envp);
	while(envp[i] != '=')
	{
		i++;
	}
	key = malloc(i + 1);
	if (key == NULL)
		printf("Smack my B*tch up!!\n");
	for (int copy_i = 0; copy_i < i; copy_i++)
	{
		key[copy_i] = envp[copy_i];
		printf("key: %c\n", key[copy_i]);
	}
	node->key = key;
	j = i;
	while(envp[i])
	{
		i++;
	}
	value = malloc(i + 1);
	if (value == NULL)
		printf("Smack my B*tch up!!\n");
	for (int copy_j = 0; copy_j < i; copy_j++)
	{
		value[copy_j] = envp[j];
		printf("value: %c\n", value[copy_j]);
		j++;
	}
	node->value = value;
	node->next = NULL;
	return (node);
}

static void	parse_envp(t_data *data, char **envp)
{
	int i;
	t_envp	*current;
	t_envp	*new_node;

	i = 0;
	current = NULL;
	new_node = NULL;
	while(envp[i])
	{
		// printf("here1\n");
		new_node = create_node(envp[i]);
		printf("This is envp[%i]: %s, %p\n", i, envp[i], new_node);
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
		// printf("here2\n");
		i++;
	}
}

void	parsing(t_data *data, char **envp)
{
	invalid_input(data);
	parse_envp(data, envp);

	t_envp *current;
	t_envp *next;
	int i = 0;
	current = data->envp_head;
	next = current->next;
	while(current->next != NULL)
	{
		printf("[%i], key: [%s], value: [%s]\n\n", i, current->key, current->value);
		current = current->next;
		next = current->next;
		i++;
	}
	//3 - Tokenization
	//4 - Parsed input
}
