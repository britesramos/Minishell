/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 07:48:37 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/25 06:56:36 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_check_help(char *cmd, t_envp *env, int len)
{
	if (ft_strchr(cmd, '=') != NULL)
	{
		while (env != NULL)
		{
			if (ft_strncmp(env->key, cmd, len) == 0)
				return (1);
			env = env->next;
		}
	}
	while (env != NULL)
	{
		if (ft_strncmp(env->key, cmd, ft_strlen(cmd) + 1) == 0)
			return (2);
		env = env->next;
	}
	return (0);
}

/// @brief checks if the cmd has correct input
/// @return -1 on error, 0 if the key doesn't exist, 1 if the value needs to be
///		updated, 2 when no action is required
static int	ft_export_check(char *cmd, t_data *data)
{
	t_envp	*env;
	int		len;
	int		check;

	len = 0;
	if (cmd[len] == '=')
		return (-1);
	while (cmd[len] && cmd[len] != '=')
	{
		if (!ft_isalpha(cmd[len]) && cmd[len] != '_')
			return (-1);
		len++;
	}
	env = data->envp_head;
	check = ft_check_help(cmd, env, len);
	if (check == 1)
		return (1);
	else if (check == 2)
		return (2);
	return (0);
}

static void	replace_export(t_data *data, char *cmd)
{
	char	*key;
	char	*value;

	key = init_key_export(cmd, data);
	value = init_value_export(cmd, data);
	replace_value(data, key, value);
	ft_free_string(&key);
	ft_free_string(&value);
}

/// @brief prints the env, adds the key & value, changes the value 
void	ft_export(char **cmd, t_data *data, int fd)
{
	int		i;
	int		check;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	i = 1;
	if (!cmd[i])
		ft_print_export(data, fd);
	else
	{
		while (cmd[i])
		{
			check = ft_export_check(cmd[i], data);
			if (check == 0)
				add_node(data, cmd[i], &data->envp_head);
			else if (check == 1)
				replace_export(data, cmd[i]);
			else if (check == -1)
				ft_export_error(cmd[i], data);
			i++;
		}
	}
}
