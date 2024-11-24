/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 13:41:18 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/24 07:56:36 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	path_error(t_data *data, char *cmd, int flag)
{
	if (flag == NO_PATH)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		clean_up(data);
		exit(127);
	}
	else if (flag == NO_COMMAND)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Command not found", STDERR_FILENO);
		clean_up(data);
		exit(127);
	}
}

static char	**ft_env_path(t_data *data)
{
	char	*path;
	char	**split_path;
	t_envp	*current;
	char	*key;

	path = NULL;
	split_path = NULL;
	current = data->envp_head;
	key = current->key;
	while (current != NULL)
	{
		key = current->key;
		if (ft_strncmp(key, "PATH", 5) == 0)
		{
			path = current->value + 1;
			break ;
		}
		current = current->next;
	}
	if (path)
		split_path = ft_split(path, ':');
	return (split_path);
}

static void	find_path(char **paths, char *cmd, char **path)
{
	int		i;

	i = 0;
	if (paths && paths[i])
	{
		while (paths[i])
		{
			*path = ft_strjoin(paths[i], cmd);
			if (access(*path, F_OK | X_OK) == 0)
				return ;
			ft_free_string(path);
			i++;
		}
	}
	else
		access(cmd, F_OK | X_OK);
}

static void	get_path(t_data *data, char *cmd, char **path)
{
	char	**all_paths;
	char	*slash_cmd;

	all_paths = ft_env_path(data);
	if (!all_paths)
		path_error(data, cmd, NO_PATH);
	slash_cmd = ft_strjoin("/", cmd);
	if (slash_cmd == NULL)
	{
		ft_putendl_fd("error: strjoin(/, cmd)", STDERR_FILENO);
		ft_free_array(all_paths);
	}
	find_path(all_paths, slash_cmd, path);
	ft_free_string(&slash_cmd);
	ft_free_array(all_paths);
	if (!*path && !path[0])
		path_error(data, cmd, NO_COMMAND);
}

void	get_path_error(t_data *data, char **path)
{
	if (ft_strchr(data->cmd_current->cmd[0], '/') != NULL)
	{
		if (access(data->cmd_current->cmd[0], F_OK | X_OK) == 0)
			*path = ft_strdup(data->cmd_current->cmd[0]);
		else
			path_error(data, data->cmd_current->cmd[0], NO_PATH);
	}
	else
		get_path(data, data->cmd_current->cmd[0], path);
}
