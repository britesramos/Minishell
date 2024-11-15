/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 08:04:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/15 09:15:45 by mstencel      ########   odam.nl         */
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
		if (ft_strncmp(env_current->key, key, len) == 0)
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
	len = ft_strlen(key);
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, len) == 0)
		{
			ft_free_string(env->value);
			env->value = ft_strjoin("=", new_value);
		}
		env = env->next;
	}
}

// t_envp	*check;
// check = *env;
// while (check != NULL)
// {
// 	ft_printf("%s%s\n", check->key, check->value);
// 	check = check->next;
// }

static t_envp	*create_node_export(t_data *data, char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		error_exit(data, NULL, "Memory allocation failed! [Node creation | envp_utils]\n", 1);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_data *data, char *cmd, t_envp **env)
{
	t_envp	*current;
	t_envp	*new_node;


	current = (*env);
	while (current->next != NULL)
		current = current->next;
	if (ft_strchr(cmd, '=') == NULL)
		new_node = create_node_export(data, cmd, NULL);
	else
		new_node = create_node_export(data, init_key_export(cmd, data), init_value_export(cmd, data));
	current->next = new_node;	
}

// export he hi ha