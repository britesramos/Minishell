/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/26 17:39:24 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/21 11:13:03 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/// @brief checks if there are any non-digit chars in cmd & 
/// displays error message if there is '(' or ')' in the argument, 
/// @return 0 when all is ok; 1 when the exit should not work; 2
/// exit should work but there is an error
static int	digit_check(char *cmd)
{
	int	i;
	int	non_digit;

	i = 0;
	non_digit = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			non_digit = 1;
		i++;
	}
	if (non_digit == 1)
		return (2);
	return (0);
}

/// @brief goes to digit_check() to check chars in cmd and 
/// displays error msg if there is a non-digit char
/// @return 0 when exit should work; 1 when it shouldn't; 
/// 2 when it should (but there is an error)
static int	is_digit_only(char *cmd, t_data *data)
{
	int	check;

	check = digit_check(cmd);
	if (check == 1)
	{
		data->exit_code = 2;
		return (1);
	}
	else if (check == 2)
	{
		data->exit_code = 2;
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" : numeric argument required", STDERR_FILENO);
		return (2);
	}
	return (0);
}

/// @brief checks: for digits only the 1st arg, if more args 
/// (and 1st is digits), doesn't work when: multiple args (all digits), ( or ).
/// Works: multiple args if the 1st arg is not a digit, # as 1st character. . .
/// from the bash man:
/// Exit the shell, returning a status of n to the shell’s parent. 
/// If n is omitted, the exit status is that of the last command executed.
/// @return returns 0 when exit should work and -9 when it shouldn't
int	ft_exit(char **cmd, t_data *data)
{
	int	digit_check;

	if (!cmd[1] || cmd[1][0] == '#')
	{
		data->exit_code = 0;
		return (0);
	}
	if (cmd[2])
	{
		ft_putendl_fd("exit", data->cmd_current->fd_out);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		data->exit_code = 1;
		return (-9);
	}
	digit_check = is_digit_only(cmd[1], data);
	if (digit_check == 1 || digit_check == 2)
		return (0);
	else
		data->exit_code = ft_atol(cmd[1]);
	if (data->exit_code < -255)
		data->exit_code = data->exit_code % -256;
	if (data->exit_code < 0)
		data->exit_code = data->exit_code + 256;
	return (0);
}

// testing on:

// works normally with 0 exit code
// ->	exit #		or exit #fgfdgdf

//the first argument matters
// EXIT WORKS ON THE PROGRAM:

// with exit code = 2 -> anything that includes: alphabet / !@$%*
// ->	exit fdsf		or		exit 45*		or		exit 
// 		exit
// 		bash: exit: fdsf: numeric argument required (when you run echo $? -> 2)

// ->	exit 24
// 		exit		(when you run echo $? -> 24)

// ->	exit $
// 		exit
// 		bash: exit: $: numeric argument required	(when you run echo $? -> 2)

//EXIT DOESN'T WORK
// ->	exit 24 53
// 		exit
// 		bash: exit: too many arguments
//			(when you run echo $?  -> 1)

// ->	exit (
// 		bash: syntax error near unexpected token `newline'   
// 			(when you run echo $?  -> 2)

// ->	exit )
// 		bash: syntax error near unexpected token `)'
// 			(when you run echo $?  -> 2)
