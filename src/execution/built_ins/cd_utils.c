/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:08:54 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/24 08:41:23 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cd_errno_error(t_data *data, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	data->exit_code = 1;
}

char	*ft_getcdw_err(t_data *data)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: cd: getpwd: ");
		data->exit_code = 2;
	}
	return (cwd);
}

char	*ft_getcwd_parent_err(t_data *data)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		data->exit_code = 2;
	}
	return (cwd);
}
