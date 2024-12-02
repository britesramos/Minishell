/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 07:48:37 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/02 09:16:16 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_compare(char *cmd, int cmd_len, t_data *data)
{
	int		key_len;
	t_envp	*env;

	env = data->envp_head;
	while (env != NULL)
	{
		key_len = ft_strlen(env->key) + 1;
		if (cmd_len >= key_len)
		{
			if (ft_strncmp(env->key, cmd, cmd_len) == 0)
				return (3);
		}
		else
		{
			if (ft_strncmp(env->key, cmd, key_len) == 0)
				return (3);
		}
		env = env->next;
	}
	return (0);
}

static int	ft_check_help(char *cmd_key, char *cmd, t_data *data, int c_k_len)
{
	t_envp	*env;

	env = data->envp_head;
	if (ft_strchr(cmd, '=') != NULL)
	{
		if (ft_compare(cmd_key, c_k_len, data) == 3)
			return (1);
	}
	else
	{
		if (ft_compare(cmd_key, c_k_len, data) == 3)
			return (2);
	}
	return (0);
}

/// @brief checks if the cmd has correct input
/// @return -1 on error, 0 if the key doesn't exist, 1 if the value needs to be
///		updated, 2 when no action is required
static int	ft_export_check(char *cmd, t_data *data)
{
	int		len;
	int		check;
	char	*cmd_key;
	int		i;

	len = ft_export_init_check(cmd);
	if (len == -1)
		return (-1);
	cmd_key = malloc(sizeof(char) * len + 1);
	if (!cmd_key)
		error_exit(data, NULL, "malloc in ft_export_check", -10);
	i = 0;
	while (i < len)
	{
		cmd_key[i] = cmd[i];
		i++;
	}
	cmd_key[i] = '\0';
	check = ft_check_help(cmd_key, cmd, data, len + 1);
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
	value = init_replace_value_export(cmd, data);
	replace_value(data, key, value);
	ft_free_string(&key);
	ft_free_string(&value);
}

/// @brief prints the env, adds the key & value, changes the value 
void	ft_export(char **cmd, t_data *data, int fd)
{
	int		i;
	int		check;

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
