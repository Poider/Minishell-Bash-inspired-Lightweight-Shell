/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:36:40 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:58:20 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_commandtable *command_table)
{
	while (command_table)
	{
		if (command_table->input_fd != 0)
			close(command_table->input_fd);
		if (command_table->output_fd != 1)
			close(command_table->output_fd);
		command_table = command_table->next;
	}
}

t_commandtable	*find_duplicate_files(t_commandtable *command_table)
{
	t_commandtable	*duplicate;
	char			*file_name;

	duplicate = 0;
	file_name = command_table->command;
	command_table = command_table->next;
	while (command_table)
	{
		if (command_table->is_a_file_a == 1 || command_table->is_a_file == 1)
		{
			if (command_table->previous)
			{
				if (command_table->previous->pipe == 1)
					break ;
			}
			if (!ft_strncmp(command_table->command, file_name, max
					(ft_strlen(file_name), ft_strlen(command_table->command))))
			{
				duplicate = command_table;
			}
		}
		command_table = command_table->next;
	}
	return (duplicate);
}

void	handle_priority(t_commandtable *file1, t_commandtable *file2)
{
	int	overwrite;

	overwrite = 0;
	if (file1->is_a_file || file2->is_a_file)
		overwrite = 1;
	if (overwrite)
	{
		file1->is_a_file_a = 0;
		file2->is_a_file_a = 0;
		file1->is_a_file = 1;
		file2->is_a_file = 1;
	}
}

void	duplicate_files(t_commandtable *command_table)
{
	t_commandtable	*duplicate;

	while (command_table)
	{
		if (command_table->is_a_file_a == 1 || command_table->is_a_file == 1)
		{
			duplicate = find_duplicate_files(command_table);
			if (duplicate)
				handle_priority(command_table, duplicate);
		}
		command_table = command_table->next;
	}
}

int	open_all(t_commandtable *command_table)
{
	t_commandtable	*head_node;
	int				open_return;

	head_node = command_table;
	while (command_table)
	{
		if (command_table->is_a_file)
			open_return = file_opener(3, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_a_file_a)
			open_return = file_opener(2, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_a_file_r)
			open_return = file_opener(1, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_heredoc)
			open_return = file_opener(0, command_table->limiter,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		command_table = command_table->next;
	}
	return (open_return);
}
