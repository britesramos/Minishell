/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 08:04:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 21:53:12 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*find_value(t_data *data, char *key)
{
	t_envp	*env_current;
	char	*value;
	int		len;

	value = NULL;
	len = ft_strlen(key) + 1;
	env_current = data->envp_head;
	while (env_current != NULL)
	{
		if (ft_strncmp(env_current->key + 1, key + 1, len) == 0)
			value = env_current->value + 1;
		env_current = env_current->next;
	}
	return (value);
}

void	replace_value(t_data *data, char *key, char *new_value)
{
	t_envp	*env;
	long	len;

	env = data->envp_head;
	len = ft_strlen(key) + 1;
	while (env != NULL)
	{
		if (ft_strncmp((env->key) + 1, key + 1, len) == 0)
		{
			ft_free_string(&env->value);
			if (ft_strncmp(new_value, "= ", ft_strlen(new_value) + 1) == 0)
			{
				env->value = ft_strdup(new_value);
				if (!env->value)
					error_exit(data, NULL, "malloc in replace_value", -10);
			}
			else
			{
				env->value = ft_strjoin("=", new_value);
				if (!env->value)
					error_exit(data, NULL, "malloc in replace_value", -10);
			}
		}
		env = env->next;
	}
}

static t_envp	*create_node_export(t_data *data, char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		error_exit(data, NULL, "malloc in create_node_export", -10);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		error_exit(data, NULL, "malloc in create_node_export", -10);
	if (value == NULL)
	{
		new_node->value = ft_strdup("");
		if (!new_node->value)
			error_exit(data, NULL, "malloc in create_node_export", -10);
	}
	else
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			error_exit(data, NULL, "malloc in create_node_export", -10);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_data *data, char *cmd, t_envp **env)
{
	t_envp	*current;
	t_envp	*new_node;
	char	*key;
	char	*value;

	current = (*env);
	while (current->next != NULL)
		current = current->next;
	if (ft_strchr(cmd, '=') == NULL)
		new_node = create_node_export(data, cmd, NULL);
	else
	{
		key = init_key_export(cmd, data);
		value = init_value_export(cmd, data);
		new_node = create_node_export(data, key, value);
		ft_free_string(&key);
		ft_free_string(&value);
	}
	current->next = new_node;
}
