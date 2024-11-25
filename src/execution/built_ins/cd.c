/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:01:06 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/25 06:55:58 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_cd_open_check(t_data *data, char *path)
{
	if (opendir(path) == NULL)
	{
		cd_errno_error(data, path);
		return (-1);
	}
	return (0);
}

static void	ft_cd_change(char *path, t_data *data)
{
	char	*old_cwd;
	char	*cwd;

	cwd = NULL;
	old_cwd = ft_getcdw_err(data);
	if (old_cwd == NULL)
		return ;
	if (chdir(path) != 0)
	{
		if (ft_cd_open_check(data, path) == -1)
		{
			ft_free_string(&old_cwd);
			return ;
		}
		cwd = ft_getcdw_err(data);
		if (cwd == NULL)
		{
			ft_free_string(&old_cwd);
			return ;
		}
		replace_value(data, "PWD", cwd);
		replace_value(data, "OLDPWD", old_cwd);
		ft_free_string(&cwd);
	}
	ft_free_string(&old_cwd);
}

/// @brief changes the current directory to path
/// @param path the destination directory
static void	ft_chdir_error(char *path, t_data *data)
{
	int		oops;
	char	*cwd;

	cwd = ft_getcwd_parent_err(data);
	if (cwd == NULL)
		return ;
	oops = chdir(path);
	if (oops != 0)
	{
		perror("minishell: cd");
		data->exit_code = 1;
		ft_free_string(&cwd);
		return ;
	}
	replace_value(data, "OLDPWD", cwd);
	ft_free_string(&cwd);
	cwd = ft_getcdw_err(data);
	if (cwd == NULL)
		return ;
	replace_value(data, "PWD", cwd);
	ft_free_string(&cwd);
	data->exit_code = 0;
}

/// @brief changes the destination based on the key word
/// @param data main struct
/// @param key key word from the envp either HOME or OLDPWD
static void	ft_cd_key(t_data *data, char *key)
{
	char	*path;

	path = find_value(data, key);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
		data->exit_code = 1;
		return ;
	}
	if (ft_strncmp(key, "OLDPWD", 7) == 0)
		ft_putendl_fd(path, data->cmd_current->fd_out);
	ft_chdir_error(path, data);
	data->exit_code = 0;
}

void	ft_cd(char **cmd, t_data *data)
{
	data->exit_code = 0;
	if (cmd[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		data->exit_code = 1;
	}
	if (!cmd[1] || ft_strncmp(cmd[1], "~", 2) == 0)
		ft_cd_key(data, "HOME");
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		ft_cd_key(data, "OLDPWD");
	else if (ft_strncmp(cmd[1], "..", 3) == 0)
		ft_chdir_error("..", data);
	else if (ft_strncmp(cmd[1], "/", 2) == 0)
		ft_chdir_error("/", data);
	else
	{
		if (access(cmd[1], F_OK) == 0)
			ft_cd_change(cmd[1], data);
		else
			cd_errno_error(data, cmd[1]);
	}
}

/*
TESTING ON:
cd		->goes to home dir
cd ~		->goes to home dir
cd #		->goes to home dir
cd ..		->goes to the parent dir
cd -		->goes to the OLDPWD and writes the absolute path to fd_out
cd /		->goes to the root (PWD = /)
cd /home/bocal -> error check :)

CD NOT WORKING (exit status: 1)
cd with any of:  !@$%^={}[]
	-> bash: cd: !: No such file or directory (exit status: 1)
cd *		-> bash: cd: too many arguments

would this be for Sara -> the same error upon any brackets ()<>
CD NOT WORKING (exit status: 2)
cd (		-> bash: syntax error near unexpected token `newline'
cd )		-> bash: syntax error near unexpected token `)'
*/

/*
cd with only a relative or absolute path (starting with /)
All relative names are treated by the kernel as relative to the current
directory — as if the name was prefixed by ./
*/

/*
from the bash man
cd changes the current working directory to directory given as an argument 
1.If directory is not supplied, the value of the HOME shell variable is used
2.If ‘..’ appears in directory, it is processed by removing the immediately
preceding pathname component, back to a slash or the beginning of directory.
3. If directory is ‘-’, it is converted to $OLDPWD before the directory
change is attempted.
4.If a non-empty directory name from CDPATH is used, or if ‘-’ is the first
argument, and the directory change is successful, the absolute pathname of
the new working directory is written to the standard output.
5.If the directory change is successful, cd sets the value of the PWD
environment variable to the new directory name, and sets the OLDPWD
environment variable to the value of the current working directory before
the change.
6.The return status is zero if the directory is successfully changed,
non-zero otherwise.
*/
