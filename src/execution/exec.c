/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 18:28:52 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/26 17:46:38 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static int	bi_valid_check(t_cmd **cmd)
{

	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (1);
	return (0);
}

static void	cmd_valid_check(t_data *data, t_cmd *current_cmd)
{

	if (bi_valid_check(current_cmd->cmd) == 1)
	{
		current_cmd->valid_cmd = true;
		return ;
	}
	get_path_error(data, &current_cmd->cmd_path);
	

}

static int	bi_check(t_data *data)
{
	int	check;

	check = ft_builtin_manager(data, data->cmd_current->fd_out);
	if (check == 9)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (9);
	}
	else if (check == 3)
		return (9);
	else if (check == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	exec(t_data *data)
{
	int		check;
	char	*path;

	check = 0;
	while (data->cmd_current)
	{
		if (data->cmd_current->cmd)
			cmd_valid_check(data, data->cmd_current);
		data->cmd_current = data->cmd_current->pipe;
	}
	if (data->nbr_pipes == 0)
	{
			check = bi_check(data);
			if (check == 9)
				return (9);
			else if (check == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			else
				single_cmd(data);
	}
	else
		mltpl_cmd(data);
	return (EXIT_SUCCESS);
}

/*
TESTING ON
cat | exit | cat | ls
cat | cat | cat ls
cat | exit | cat test | ls
ls -l >test | wc -l < test > test2 | pwd
*/