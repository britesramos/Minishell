/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_manager.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:05:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/15 09:10:03 by mstencel      ########   odam.nl         */
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
int	ft_builtin_manager(t_data *data, int fd)
{
	char	**cmd;

	cmd = data->cmd_current->cmd;
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (ft_cd(cmd, data), 0);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (ft_echo(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (ft_env(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		if (ft_exit(cmd, data) == 0)
			return (9);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (ft_export(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (ft_pwd(cmd, data, fd), 0);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (ft_unset(cmd, data), 0);
	return (EXIT_FAILURE);
}
