/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_manager.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:05:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/03 13:10:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// TODO---!
// 		  v
//once the data->cmd's are populated, delete the char **cmd + 
// change the names of the commands and len values!
//pass only data? see how the structs are working

/// @brief checks if a cmd is a builtin, if not increments the number of kids
/// @return 0 when cmd=builtin, 9 when exit should work, 1 when cmd != builtin
int	ft_builtin_manager(t_data *data)
{
	char	**cmd;

	cmd = data->cmd_current->cmd;
	if (ft_strncmp(cmd[0], "mycd", 6) == 0)
		return (ft_cd(cmd, data), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "myecho", 8) == 0)
		return (ft_echo(cmd, data, data->cmd_current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "myenv", 6) == 0)
		return (ft_env(cmd, data, data->cmd_current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "myexit", 8) == 0)
	{
		if (ft_exit(cmd, data) == 0)
			return (9);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd[0], "myexport", 9) == 0)
		return (ft_export(cmd, data, data->cmd_current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "mypwd", 7) == 0)
		return (ft_pwd(cmd, data, data->cmd_current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "myunset", 8) == 0)
		return (ft_unset(cmd, data), EXIT_SUCCESS);
	data->kids++;
	return (EXIT_FAILURE);
}
