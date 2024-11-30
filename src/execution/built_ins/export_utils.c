/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 12:37:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/30 14:56:25 by mstencel      ########   odam.nl         */
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
		error_exit(data, NULL, "malloc in init_key_export", -10);
	while (i < key_len)
	{
		key[i] = cmd[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*init_value_export(char *cmd, t_data *data)
{
	size_t	key_len;
	size_t	cmd_len;
	char	*value;

	key_len = 0;
	value = NULL;
	cmd_len = ft_strlen(cmd);
	while (cmd[key_len] != '=')
		key_len++;
	if (key_len + 1 == cmd_len)
		key_len++;
	if (cmd_len == key_len)
	{
		value = ft_strdup("= ");
		if (!value)
			error_exit(data, NULL, "malloc 1 in init_value_export", -10);
	}
	else
	{
		value = ft_calloc(cmd_len - key_len + 1, 1);
		if (!value)
			error_exit(data, NULL, "malloc 2 in init_value_export", -10);
		ft_strlcpy(value, cmd + key_len, (size_t)cmd - key_len);
	}
	return (value);
}
