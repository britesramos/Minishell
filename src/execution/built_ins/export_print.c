/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 09:09:23 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/23 10:48:28 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_size(t_envp *current)
{
	t_envp	*env;
	int		i;

	i = 0;
	env = current;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static void	ft_print_key_value(char *key, char *value, t_data *data, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(key, fd);
	if (ft_strncmp(value, "= ", 3) == 0)
		ft_putendl_fd("=\"\"", fd);
	else if (ft_strchr(value, '=') == NULL)
		ft_putchar_fd('\n', fd);
	else
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(value + 1, fd);
		ft_putendl_fd("\"", fd);
	}
	data->exit_code = 0;
}

static t_envp	*find_to_print(t_envp *last_p, t_envp *env)
{
	t_envp	*to_p;

	to_p = NULL;
	while (env != NULL)
	{
		if (last_p == NULL || \
			ft_strncmp(last_p->key, env->key, ft_strlen(last_p->key) + 1) < 0)
		{
			if (to_p == NULL || \
				ft_strncmp(to_p->key, env->key, ft_strlen(env->key) + 1) > 0)
				to_p = env;
		}
		env = env->next;
	}
	return (to_p);
}

void	ft_print_export(t_data *data, int fd)
{
	t_envp	*current;
	t_envp	*save_head;
	t_envp	*last_p;
	int		l_size;
	int		printed;

	l_size = ft_size(data->envp_head);
	last_p = NULL;
	printed = 0;
	save_head = data->envp_head;
	while (printed < l_size)
	{
		current = save_head;
		last_p = find_to_print(last_p, current);
		ft_print_key_value(last_p->key, last_p->value, data, fd);
		printed++;
	}
}

void	ft_export_error(char *cmd, t_data *data)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier ", STDERR_FILENO);
	data->exit_code = 1;
}
