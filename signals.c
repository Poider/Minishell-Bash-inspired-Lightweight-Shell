/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:49:11 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 11:53:04 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse)
{
	char	c;

	c = '\n';
	signum += 0;
	write(1, &c, 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	in_herdoc(int signum)
{
	char	c;

	c = '\n';
	write(1, &c, 1);
}

void	ctrl_backslash_handler(int signum)
{
	signum += 0;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	get_parent_id(int signum, siginfo_t *siginfo, void *noUse)
{
	g_v_lines->parent_id = siginfo->si_pid;
}

int	handle_signals(void)
{
	g_v_lines->sa.sa_sigaction = &ctrl_c_handler;
	g_v_lines->sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &g_v_lines->sa, 0);
	signal(SIGQUIT, &ctrl_backslash_handler);
	return (1);
}