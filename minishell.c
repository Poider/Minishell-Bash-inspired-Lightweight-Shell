/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:10 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:26:06 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_line_processing_history *g_v_lines)
{
	if (!expandline(g_v_lines))
		return (0);
	return (1);
}

int	processline(t_line_processing_history *g_v_lines)
{
	int	parse_success;

	g_v_lines->trimmed_line = ft_strtrim(g_v_lines->entered_line, " 		");
	if (!ft_strncmp(g_v_lines->trimmed_line, "exit", \
			max(ft_strlen(g_v_lines->trimmed_line), 4)))
	{
		printf("exit\n");
		handle_exit();
	}
	parse_success = parse(g_v_lines);
	if (parse_success)
		parse_success = process_command_table(g_v_lines);
	if (parse_success)
		execute(g_v_lines);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)(argc);
	(void)(argv);
	g_v_lines = malloc(sizeof(t_line_processing_history));
	initialize_v_lines(g_v_lines, env);
	g_v_lines->env_vars_head = env_vars_list(g_v_lines->env_vars);
	handle_signals();
	return (readline_loop(g_v_lines));
	return (1);
}
