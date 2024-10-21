/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 07:31:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/21 10:22:58 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void unset_error(char *cmd, t_data *data)
{
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
	data->exit_code = 1;
}

static int	unset_check(char *cmd, t_data *data)
{
	int	i;
	
	if (!ft_isalpha(cmd[0]))
	{
		unset_error(cmd, data);
		return (1);
	}
	i = 0;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]))
		{
			unset_error(cmd, data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	do_unset(char *cmd, t_data *data, int len, t_envp **previous)
{
	t_envp	*current;

	current	= data->envp_head;
	while (current != NULL)
	{
		if (ft_strncmp(cmd, current->key, len) == 0)
		{
			if (previous == NULL)
				data->envp_head = current->next;
			else
				(*previous)->next = current->next;
			if (current->value != NULL)
			{
				free (current->value);
				current->value = NULL;
			}
			free (current->key);
			current->key = NULL;
			free (current);
			return;
		}
		(*previous) = current;
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
		previous = NULL;
		if (unset_check(cmd[i], data) == 1)
			return ;
		len = ft_strlen(cmd[i]) + 1;
		do_unset(cmd[i], data, len, &previous);
		i++;
	}
}


/*
TEST CASES [hello & hi variables are valid]
unset hello
unset 3fdsfs
unset hello fd-fdsfs hi 
*/