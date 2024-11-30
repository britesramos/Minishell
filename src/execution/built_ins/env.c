/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 09:58:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 15:32:28 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// env without any options or arguments

static void	ft_env_arg_option(char *cmd, t_data *data)
{
	if (cmd[0] == '-')
	{
		if (cmd[1] == '-')
			cmd_extra_error("env: unrecognised option '", cmd, "'", data);
		else
			cmd_extra_error("env: invalid option --", cmd, "'", data);
		data->exit_code = 125;
		return ;
	}
	cmd_extra_error("env: '", cmd, "': No such file or directory", data);
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
