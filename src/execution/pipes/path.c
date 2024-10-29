/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 13:41:18 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/29 12:48:37 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**ft_env_path(t_data *data)
{
	char	*path;
	char	**split_path;
	t_envp	*current;
	
	path = NULL;
	current = data->envp_head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "PATH", 5) == 0)
		{
			path = current->value + 1;
			break ;
		}
		current = current->next;
	}
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		ft_putendl_fd("couldn't get **all_paths from envp", STDERR_FILENO);
	return (split_path);
}

char	*find_path(char **paths, char *cmd)
{
	char	*right_path;
	int		i;

	right_path = NULL;
	i = 0;
	while (paths[i])
	{
		right_path = ft_strjoin(paths[i], cmd);
		if (access(right_path, X_OK) == 0)
			return (right_path);
		free (right_path);
		i++;
	}
	if (right_path == NULL)
		ft_putendl_fd("error: path not matched with the cmd", STDERR_FILENO);
	return (right_path);
}

char	*get_path(t_data *data, char *cmd)
{
	char	**all_paths;
	char	*path;
	char	*slash_cmd;

	all_paths = ft_env_path(data);
	if (all_paths == NULL)
		return (NULL);
	slash_cmd = ft_strjoin("/", cmd);
	if (slash_cmd == NULL)
	{
		ft_putendl_fd("error: strjoin(/, cmd)", STDERR_FILENO);
		ft_free(all_paths);
		return (NULL);
	}
	path = find_path(all_paths, slash_cmd);
	free(slash_cmd);
	ft_free(all_paths);
	return (path);
}
