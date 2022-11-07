/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2_command_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:20:07 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:26:58 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_into_table(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	if (command_table->is_a_command)
		fill_command(line, command_table);
	else if (command_table->is_a_file || command_table->is_a_file_a
		|| command_table->is_a_file_r)
		fill_file(line, command_table);
	else if (command_table->is_heredoc)
		fill_limiter(line, command_table);
	return (1);
}

static void	skip_quotes(t_iters5 *iters, char *line)
{
	int	j;

	j = line[iters->start_iter];
	iters->start_iter++;
	iters->len++;
	while (line[iters->start_iter] != j && line[iters->start_iter])
	{
		iters->start_iter++;
		iters->len++;
	}
}

void	e_l_2_c_d_compliment(t_iters5 iters, char *line, int redirection_number)
{
	if (iters.len && !is_full_of_whitespaces(line))
	{
		initialize_command_table_node(g_v_lines);
		iters.command_table = get_last_command_line(g_v_lines->command_table);
		fill_command_type(iters.command_table, iters.previous_redirection);
		g_v_lines->is_next_a_command = 0;
		if (redirection_number == 10)
			iters.command_table->pipe = 1;
		else if (redirection_number)
		{
			iters.command_table->redirections = redirection_number;
			fill_is_a_command(g_v_lines, redirection_number);
		}
		split_into_table(line, iters.command_table);
	}
	else
		fill_is_a_command(g_v_lines, redirection_number);
}

int	expanded_line_2_command_table(t_line_processing_history *g_v_lines,
		int start, int redirection_number, char *line)
{
	t_iters5	iters;

	(void)(g_v_lines);
	iters.start_iter = start;
	iters.len = 0;
	iters.previous_redirection = check_previous_redirection(line, start);
	while (!reached_a_redirection_or_end(line[iters.start_iter]))
	{
		if (line[iters.start_iter] == 34 || line[iters.start_iter] == 39)
			skip_quotes(&iters, line);
		iters.start_iter++;
		iters.len++;
	}
	iters.temp = line;
	line = ft_substr(line, start, iters.len);
	free(iters.temp);
	e_l_2_c_d_compliment(iters, line, redirection_number);
	free(line);
	return (1);
}
