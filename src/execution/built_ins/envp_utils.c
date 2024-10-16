/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 08:04:38 by mstencel      #+#    #+#                 */
/*   Updated: 2024/10/11 13:36:21 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*find_value(t_data *data, char *key)
{
	t_envp	*env_current;
	char	*value;
	int		len;

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
			// ft_printf("1. before the change: env->value in %s at %p is %s\n", env->key, env->value, env->value);
			free(env->value);
			env->value = NULL;
			env->value = ft_strjoin("=", new_value);
			// ft_printf("2. after the change: env->value in %s at %p is %s\n", env->key, env->value, env->value);
		}
		env = env->next;
	}
}
