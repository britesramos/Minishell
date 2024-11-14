/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 17:55:59 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/14 14:21:15 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


static void	signal_parent(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_redisplay();
	}
}

static void	signal_child_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

static void signal_child_s(int signal)
{
	if (signal == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)", 18);
}
void	signal_hd(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	ms_signals(int process)
{

	if (process == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_parent);
	}
	else if (process == CHILD)
	{
		signal(SIGINT, signal_child_c);
		signal(SIGQUIT, signal_child_s);
	}
	else if (process == HEREDOCP)
	{
		signal(SIGINT, signal_hd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == HEREDOCC)
	{
		ft_putendl_fd("elo", 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}

}
	
// 	struct sigaction	sa;

// 	ft_memset(&sa, 0, sizeof(sa));
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGINT);
// 	sigaddset(&sa.sa_mask, SIGQUIT);

// 	sa.sa_sigaction = &handles;
// 	sa.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGINT, &sa, NULL) == -1 || 
// 		sigaction(SIGQUIT, &sa, NULL) == -1)
// 	{
// 		perror("SIGINT error");
// 		data->exit_code = errno;
// 		return ;
// 	}
// }
// static void	handles(int signal, siginfo_t *info, void *x)
// {
// 	if (info || x)
// 		printf("1\n");
// 	if (signal == SIGINT)
// 	{
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		ft_putendl_fd("in handles?", STDOUT_FILENO);
// 	}
// 	else if (signal == SIGQUIT)
// 		printf("I'm not me\n");
// 	else if (signal == SIGTERM)
// 		printf("what am I?\n");
// }