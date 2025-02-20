/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:29:27 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:30:56 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	waiting(void)
{
	int	j;

	waitpid(-1, &j, 0);
	if (j == 2)
		g_v_lines->exit_status = 1;
	else
		g_v_lines->exit_status = WEXITSTATUS(j);
	if (g_v_lines->failure)
		g_v_lines->exit_status = g_v_lines->failure;
	g_v_lines->failure = 0;
}

static void	exiting_loop(void)
{
	close_fds(g_v_lines->command_table);
	free_all(g_v_lines);
	free_env(g_v_lines->env_vars);
	exit(g_v_lines->exit_status);
}

int	readline_loop(t_line_processing_history *g_v_lines)
{
	while (1)
	{
		handle_signals();
		g_v_lines->entered_line = readline("bash tsetta -0.1 $ ");
		if (!g_v_lines->entered_line)
		{
			printf("exit\n");
			handle_exit();
		}
		if (!is_full_of_whitespaces(g_v_lines->entered_line))
		{
			add_history(g_v_lines->entered_line);
			processline(g_v_lines);
		}
		if (g_v_lines->parent_id != 0)
			waiting();
		else
			exiting_loop();
		free_all(g_v_lines);
	}
}
