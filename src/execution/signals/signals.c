/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstencel <mstencel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 17:55:59 by mstencel      #+#    #+#                 */
/*   Updated: 2024/11/21 11:32:21 by mstencel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

/// @brief this is for the non-interactive mode (no input from the terminal)
static void	signal_p(int signal, siginfo_t *info, void *x)
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

/// @brief this is for the interactive mode (input from the terminal)
static void	signal_int(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sign = signal;
	}
}

static void	signal_help(int process, struct sigaction *sa)
{
	if (process == NONINTERACTIVE)
	{
		sa->sa_sigaction = &signal_p;
		if (sigaction(SIGINT, sa, NULL) == -1)
		{
			perror("SIGINT error");
			return ;
		}
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == INTERACTIVE)
	{
		sa->sa_sigaction = &signal_int;
		if (sigaction(SIGINT, sa, NULL) == -1)
		{
			perror("SIGINT error");
			return ;
		}
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ms_signals(int process)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	if (process == NONINTERACTIVE || process == INTERACTIVE)
		signal_help(process, &sa);
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
