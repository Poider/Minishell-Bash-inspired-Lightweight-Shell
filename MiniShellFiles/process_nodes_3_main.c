/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes_3_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:41:56 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:28:07 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_table_node(t_commandtable *command_table)
{
	t_commandtable	*previous_temp;
	t_commandtable	*next_temp;

	previous_temp = command_table->previous;
	next_temp = command_table->next;
	if (command_table->command)
		free(command_table->command);
	if (command_table->limiter)
		free(command_table->limiter);
	free(command_table);
	if (previous_temp)
		previous_temp->next = next_temp;
	else
		g_v_lines->command_table = next_temp;
	if (next_temp)
		next_temp->previous = previous_temp;
}

int	clean_nodes(t_commandtable *command_table)
{
	t_commandtable	*temp;

	while (command_table)
	{
		temp = command_table->next;
		if (command_table->is_a_command == 0)
			delete_table_node(command_table);
		command_table = temp;
	}
	return (1);
}

void	transfer_node_infos(t_commandtable *node_to_fill,
			t_commandtable *current_node)
{
	if (current_node->self_input_fd != -1)
	{
		if (node_to_fill->input_fd != 0)
			close(node_to_fill->input_fd);
		node_to_fill->input_fd = current_node->self_input_fd;
	}
	if (current_node->self_output_fd != -1)
	{
		if (node_to_fill->output_fd != 1)
			close(node_to_fill->output_fd);
		node_to_fill->output_fd = current_node->self_output_fd;
	}
	link_argument_nodes(node_to_fill, current_node);
}

int	process_command_table_compliment_0(t_commandtable *current_node,
		t_commandtable *node_to_fill, int built_in_number)
{
	while (current_node)
	{
		node_to_fill = get_node_to_fill(current_node);
		if (current_node != node_to_fill)
		{
			transfer_node_infos(node_to_fill, current_node);
		}
		current_node = current_node->next;
	}
	clean_nodes(g_v_lines->command_table);
	process_wildcards(g_v_lines->command_table);
	if (built_in_number)
		execute_built_in_parent(built_in_number);
	return (0);
}

int	process_command_table(t_line_processing_history *g_v_lines)
{
	t_iters9		iter;

	iter.current_node = g_v_lines->command_table;
	duplicate_files(iter.current_node);
	iter.built_in_number = is_built_in(g_v_lines);
	signal(SIGINT, &in_herdoc);
	g_v_lines->parent_id = fork();
	if (g_v_lines->parent_id != 0)
		return (process_command_table_compliment_0(iter.current_node, \
			iter.node_to_fill, iter.built_in_number));
	signal(SIGINT, SIG_DFL);
	if (open_all(iter.current_node) == 0)
		return (0);
	while (iter.current_node)
	{
		iter.node_to_fill = get_node_to_fill(iter.current_node);
		if (iter.current_node != iter.node_to_fill)
			transfer_node_infos(iter.node_to_fill, iter.current_node);
		iter.current_node = iter.current_node->next;
	}
	clean_nodes(g_v_lines->command_table);
	process_wildcards(g_v_lines->command_table);
	if (iter.built_in_number)
		execute_built_in_first_child(iter.built_in_number);
	return (1);
}
