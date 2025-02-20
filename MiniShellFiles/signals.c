/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:49:11 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:30:03 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse)
{
	char	c;

	(void)(siginfo);
	(void)(noUse);
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

	(void)(signum);
	c = '\n';
	write(1, &c, 1);
}

void	ctrl_backslash_handler(int signum)
{
	(void)(signum);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	get_parent_id(int signum, siginfo_t *siginfo, void *noUse)
{
	(void)(signum);
	(void)(noUse);
	g_v_lines->parent_id = siginfo->si_pid;
}

int	handle_signals(void)
{
	g_v_lines->sa.sa_sigaction = &ctrl_c_handler;
	g_v_lines->sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &g_v_lines->sa, 0);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
