/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:28:29 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:30:52 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_is_a_command(t_line_processing_history *g_v_lines,
	int redirection_number)
{
	if (redirection_number == 1)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 2)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 3)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 4)
		g_v_lines->is_next_a_command = 2;
	return (1);
}

int	fill_command_type(t_commandtable *command_table, int type)
{
	if (type == 0 || type == 10)
	{
		command_table->is_a_command = 1;
		g_v_lines->got_command_yet = 1;
	}
	else if (type == 1)
		command_table->is_a_file = 1;
	else if (type == 3)
		command_table->is_a_file_r = 1;
	else if (type == 4)
		command_table->is_heredoc = 1;
	else if (type == 2)
		command_table->is_a_file_a = 1;
	return (1);
}

void	fill_command(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void	fill_file(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void	fill_limiter(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->limiter = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

