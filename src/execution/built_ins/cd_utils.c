/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 09:08:54 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 14:27:03 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cd_errno_error(t_data *data, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(": ", strerror(errno));
	if (!tmp)
		error_exit(data, NULL, "malloc in cd_errno_error", -10);
	mini_error(path, tmp, data);
	ft_free_string(&tmp);
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
	char	*tmp;
	char	*tmp1;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	tmp = NULL;
	tmp1 = NULL;
	if (cwd == NULL)
	{
		tmp = ft_strjoin("cd: error retrieving current directory: ", \
			"getcwd: cannot access parent directories: ");
		tmp1 = ft_strjoin(tmp, "No such file or directory");
		ft_putendl_fd(tmp1, STDERR_FILENO);
		data->exit_code = 2;
		ft_free_string(&tmp);
		ft_free_string(&tmp1);
	}
	return (cwd);
}
