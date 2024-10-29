/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_manager.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:05:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 08:29:59 by mstencel      ########   odam.nl         */
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
int	ft_builtin_manager(t_data *data, t_cmd *current)
{
	char	**cmd;

	cmd = current->cmd;
	if (ft_strncmp(cmd[0], "my_cd", 6) == 0)
		return (ft_cd(cmd, data), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "my_echo", 8) == 0)
		return (ft_echo(cmd, data, current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "my_env", 6) == 0)
		return (ft_env(cmd, data, current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "my_exit", 8) == 0)
	{
		if (ft_exit(cmd, data) == 0)
			return (9);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd[0], "my_export", 9) == 0)
		return (ft_export(cmd, data, current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "my_pwd", 7) == 0)
		return(ft_pwd(cmd, data, current->fd_out), EXIT_SUCCESS);
	else if (ft_strncmp(cmd[0], "my_unset", 8) == 0)
		return (ft_unset(cmd, data), EXIT_SUCCESS);
	data->kids++;
	return (EXIT_FAILURE);
}
