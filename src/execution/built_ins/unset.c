/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 07:31:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/21 10:59:34 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	unset_node(t_envp **current)
{
	if ((*current)->value != NULL)
	{
		free ((*current)->value);
		(*current)->value = NULL;
	}
	free ((*current)->key);
	(*current)->key = NULL;
	free ((*current));
}

static void	do_unset(char *cmd, t_data *data, int len)
{
	t_envp	*current;
	t_envp	*previous;

	current	= data->envp_head;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(cmd, current->key, len) == 0)
		{
			if (previous == NULL)
				data->envp_head = current->next;
			else
				previous->next = current->next;
			unset_node(&current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(char **cmd, t_data *data)
{
	t_envp	*previous;
	int		len;
	int		i;
	
	i = 1;
	if (!cmd[i])
	{
		data->exit_code = 0;
		return ;
	}
	while (cmd[i])
	{
		len = ft_strlen(cmd[i]) + 1;
		do_unset(cmd[i], data, len);
		i++;
	}
	data->exit_code = 0;
}


/*
TEST CASES [hello & hi variables are valid]
unset hello
unset 3fdsfs
unset hello fd-fdsfs hi
unset SHELL
*/