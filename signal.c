/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:24:19 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/06 14:56:58 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	par_sig_handler(int sig)
{
	if (sig)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = sig;
	}
}

void	child_sig_c(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_first(int sig)
{
	g_sig = sig;
}

void	set_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, par_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, child_sig_c);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 2)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 3)
	{
		signal(SIGINT, handle_first);
		signal(SIGQUIT, SIG_IGN);
	}
}
