/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_p.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 16:00:05 by sramos        #+#    #+#                 */
/*   Updated: 2024/11/25 14:57:52 by sramos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_exit_system(t_data *data, char *str, t_cmd *cmd, int type)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->error == NULL)
	{
		cmd->error = ft_strjoin(str, ": ");
		tmp = ft_strjoin("minishell: ", cmd->error);
		ft_free_string(&cmd->error);
		cmd->error = ft_strjoin(tmp, strerror(errno));
		ft_free_string(&tmp);
	}
	data->exit_code = type;
	return (0);
}

int	error_exit(t_data *data, char *file, char *str, int type)
{
	int	len;
	int	lenfile;

	len = ft_strlen(str);
	lenfile = 0;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (file)
	{
		lenfile = ft_strlen(file);
		write(STDERR_FILENO, file, lenfile);
	}
	write(STDERR_FILENO, str, len);
	data->exit_code = type;
	return (0);
}
