/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_files_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:10:56 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:32:59 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	opening_herdoc(t_commandtable *command_table)
{
	int				open_return;

	open_return = 1;
	if (command_table->is_heredoc && command_table->quote_in_limiter)
			open_return = file_opener(0, command_table->limiter,
				&command_table->self_input_fd,
				&command_table->self_output_fd);
	else if (command_table->is_heredoc && \
							!command_table->quote_in_limiter)
			open_return = file_opener(-1, command_table->limiter, \
			&command_table->self_input_fd, \
			&command_table->self_output_fd);
	return (open_return);
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
		else
			open_return = opening_herdoc(command_table);
		command_table = command_table->next;
	}
	return (open_return);
}
