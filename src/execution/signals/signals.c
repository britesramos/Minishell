/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 17:55:59 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/20 09:39:53 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// static void	signal_parent(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		rl_redisplay();
// 	}
// }

// static void	signal_child_int(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	}
// }

// void	signal_hd(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		close (STDERR_FILENO);
// 		close (STDIN_FILENO);
// 		close (STDOUT_FILENO);
// 	}
// }

// void	ms_signals(int process)
// {
// 	if (process == PARENT)
// 	{
// 		signal(SIGINT, signal_parent);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (process == CHILD)
// 	{
// 		signal(SIGINT, signal_child_int);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	else if (process == HEREDOC)
// 	{
// 		signal(SIGINT, signal_hd);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// }

						/*for the sigaction*/

extern volatile sig_atomic_t	g_sign;

static void	signal_hd(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;
		if (signal == SIGINT)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			g_sign = signal;
		}

}

static void	signal_p(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;
	if (signal == SIGINT)
	{
		// ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd("noninteractive\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sign = signal;
	}
}

static void	signal_int(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;
	if (signal == SIGINT)
	{
		// ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd("interactive\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sign = signal;
	}
}

void	ms_signals(int process)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	if (process == NONINTERACTIVE)
	{
		sa.sa_sigaction = &signal_p;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("SIGINT error");
			return ;
		}
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == INTERACTIVE)
	{
		sa.sa_sigaction = &signal_int;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("SIGINT error");
			return ;
		}
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == HEREDOC)
	{
		sa.sa_sigaction = &signal_hd;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("SIGINT error");
			return ;
		}
		signal(SIGQUIT, SIG_IGN);
	}
}
