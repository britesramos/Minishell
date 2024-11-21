/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosia <gosia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:48:37 by mstencel          #+#    #+#             */
/*   Updated: 2024/11/21 20:51:46 by gosia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*init_key_export(char *cmd, t_data *data)
{
	int		i;
	int		key_len;
	char	*key;

	i = 0;
	key_len = 0;
	key = NULL;
	while (cmd[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	if (!key)
	{
		perror("export - key creation");
		data->exit_code = 1;
		return (NULL);
	}
	while (i < key_len)
	{
		key[i] = cmd[i];
		i++;
	}
	key[i] = '\0';
	printf("key: %s\n", key);
	return (key);
}

char	*init_value_export(char *cmd, t_data *data)
{
	int		i;
	size_t	key_len;
	size_t	cmd_len;
	char	*value;

	i = 0;
	key_len = 0;
	value = NULL;
	cmd_len = ft_strlen(cmd);
	while (cmd[key_len] != '=')
		key_len++;
	if (key_len + 1 == cmd_len)
		key_len++;
	if (cmd_len - key_len == 0)
		return (value);
	value = ft_calloc(cmd_len - key_len + 1, 1);
	if (!value)
	{
		perror("export - value creation");
		data->exit_code = 1;
		return (NULL);
	}
	// if (cmd_len - key_len == 0)
	// 	value[0] = '\0';
	else
		ft_strlcpy(value, cmd + key_len, (size_t)cmd - key_len);
	return (value);
}

/// @brief checks if the cmd has correct input
/// @return -1 on error, 0 if the key doesn't exist, 1 if the value needs to be
///		updated, 2 when no action is required
static int	ft_export_check(char *cmd, t_data *data)
{
	t_envp	*env;
	int		len;

	len = 0;
	if (!ft_isalpha(cmd[0]))
		return (-1);
	env = data->envp_head;
	if (ft_strchr(cmd, '=') != NULL)
	{
		while (cmd[len] != '=')
			len++;
		while (env != NULL)
		{
			if (ft_strncmp(env->key, cmd, len - 1) == 0)
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
