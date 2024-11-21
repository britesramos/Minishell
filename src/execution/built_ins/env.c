/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 09:58:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/21 09:28:39 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// env without any options or arguments

static void	ft_env_arg_option(char *cmd, t_data *data)
{
	if (cmd[0] == '-')
	{
		if (cmd[1] == '-')
		{
			ft_putstr_fd("env: unrecognised option '", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("env: invalid option --", STDERR_FILENO);
			ft_putchar_fd(cmd[1], STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
		}
		data->exit_code = 125;
		return ;
	}
	ft_putstr_fd("env: '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd("': No such file or directory", STDERR_FILENO);
	data->exit_code = 127;
}

void	ft_env(char **cmd, t_data *data, int fd)
{
	t_envp	*current;

	data->exit_code = 0;
	if (cmd[1])
		ft_env_arg_option(cmd[1], data);
	current = data->envp_head;
	while (current != NULL)
	{
		if (ft_strncmp(current->value, "", 1) != 0)
		{
			ft_putstr_fd(current->key, fd);
			ft_putendl_fd(current->value, fd);
		}
		current = current->next;
	}
}
