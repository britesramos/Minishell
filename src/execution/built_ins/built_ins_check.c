/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_ins_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:05:25 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/21 08:44:41 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//once the data->cmd's are populated, delete the char **cmd + 
// change the names of the commands and len values!
//pass only data? see how the structs are working
int	ft_built_in_check(char **cmd, t_data *data)
{
	int	len;

	len = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0], "my_cd", 6) == 0)
		return (ft_cd(cmd, data), 0);
	else if (len == 7 && ft_strncmp(cmd[0], "my_echo", 8) == 0)
		return (ft_echo(cmd, data), 0);
	else if (len == 6 && ft_strncmp(cmd[0], "my_env", 6) == 0)
		return (ft_env(cmd, data), 0);
	else if (len == 7 && ft_strncmp(cmd[0], "my_exit", 8) == 0)
	{
		if (ft_exit(cmd, data) == 0)
		return (9); //TODO -> should exit ONLY when there is no other cmd-pipe
	}
	else if (len == 9 && ft_strncmp(cmd[0], "my_export", 9) == 0)
		return (ft_export(cmd, data), 0);
	else if (len == 6 && ft_strncmp(cmd[0], "my_pwd", 7) == 0)
		return(ft_pwd(cmd, data), 0);
	else if (len == 8 && ft_strncmp(cmd[0], "my_unset", 8) == 0)
		return (ft_unset(cmd, data), 0);
	return (0);
}
