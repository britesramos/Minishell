/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 07:48:37 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/04 14:04:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*init_key(char *cmd, t_data *data)
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
	return (key);
}

static char	*init_value(char *cmd, t_data *data)
{
	int		i;
	size_t	key_len;
	char	*value;

	i = 0;
	key_len = 0;
	value = NULL;
	while (cmd[key_len] != '=')
		key_len++;
	key_len++;
	value = ft_calloc(strlen(cmd) - key_len + 1, 1);
	if (!value)
	{
		perror("export - value creation");
		data->exit_code = 1;
		return (NULL);
	}
	while ((i + key_len) < ft_strlen(cmd))
	{
		value[i] = cmd[key_len + i];
		i++;
	}
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

static void	ft_export_error(char *cmd, t_data *data)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier ", STDERR_FILENO);
	data->exit_code = 1;
}

/// @brief prints the env, adds the key & value, changes the value 
void	ft_export(char **cmd, t_data *data, int fd)
{
	int	i;
	int	check;

	i = 1;
	if (!cmd[i])
		ft_print_export(data, fd);
	else
	{
		while (cmd[i])
		{
			check = ft_export_check(cmd[i], data);
			if (check == 0)
			{
				ft_printf("here\n");
				add_node(data, cmd[i], &data->envp_head);
			}
			else if (check == 1)
				replace_value(data, init_key(cmd[1], data), \
					init_value(cmd[1], data));
			else if (check == -1)
				ft_export_error(cmd[i], data);
			i++;
		}
	}
}
