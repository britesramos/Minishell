/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/24 12:37:47 by mstencel      #+#    #+#                 */
/*   Updated: 2024/12/02 09:16:41 by mstencel      ########   odam.nl         */
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
	while (cmd[key_len] && cmd[key_len] != '=')
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
	int		i;
	int		j;
	int		value_len;
	char	*value;

	i = 0;
	while (cmd[i] != '=')
		i++;
	value_len = ft_strlen(cmd) - i;
	if (value_len == 1)
		value = ft_strdup("= ");
	else
	{
		value = malloc(sizeof(char) * value_len + 1);
		if (!value)
			error_exit(data, NULL, "malloc in init_value_export", -10);
		j = 0;
		while (j < value_len)
		{
			value[j] = cmd[i + j];
			j++;
		}
		value[j] = '\0';
	}
	return (value);
}

char	*init_replace_value_export(char *cmd, t_data *data)
{
	int		i;
	int		j;
	int		value_len;
	char	*value;

	i = 0;
	while (cmd[i] != '=')
		i++;
	i++;
	value_len = ft_strlen(cmd) - i;
	value = malloc(sizeof(char) * value_len + 1);
	if (!value)
		error_exit(data, NULL, "malloc in init_value_export", -10);
	j = 0;
	while (j < value_len)
	{
		value[j] = cmd[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

int	ft_export_init_check(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[len] == '=' || ft_isdigit(cmd[len]))
		return (-1);
	while (cmd[len] && cmd[len] != '=')
	{
		if (!ft_isalnum(cmd[len]) && cmd[len] != '_')
			return (-1);
		len++;
	}
	return (len);
}
