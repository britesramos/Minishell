/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sramos <sramos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 15:18:51 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/21 13:39:04 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_envp(t_envp *envp_head)
{
	t_envp	*next;

	while (envp_head)
	{
		next = envp_head->next;
		// printf("to free %s at %p %s at %p\n", envp_head->key, envp_head->key, \
		// envp_head->value, envp_head->value);
		if (envp_head->key)
			ft_free_string(&envp_head->key);
		if (envp_head->value)
			ft_free_string(&envp_head->value);
		free(envp_head);
		envp_head = NULL;
		envp_head = next;
	}
}

void	clean_up(t_data *data)
{
	free_envp(data->envp_head);
	free_cmd_list(data->cmd_head);
	free(data->line); /*This might have to be changed if readline is a loop, so it will alocate multiple times for line.*/
	free(data);
	rl_clear_history();
}

void	free_split(char **array)
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
