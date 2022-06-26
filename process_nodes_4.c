/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:50:33 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:50:50 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	link_argument_nodes(t_commandtable *node_to_fill,
		t_commandtable *current_node)
{
	t_arguments	*last_element;
	t_arguments	*child_args_head;
	t_arguments	*parent_args_head;

	parent_args_head = node_to_fill->argument;
	child_args_head = current_node->argument;
	current_node->argument = 0;
	last_element = get_last_argument(parent_args_head);
	if (!last_element)
		node_to_fill->argument = child_args_head;
	else
		last_element->next = child_args_head;
	if (child_args_head)
		child_args_head->previous = last_element;
}

t_commandtable	*get_table_after_pipe(t_commandtable *current_node)
{
	t_commandtable	*command_table;

	command_table = current_node;
	while (command_table->previous)
	{
		if (command_table->previous->pipe == 1)
			break ;
		command_table = command_table->previous;
	}
	return (command_table);
}



void	get_node_to_fill_compliment(t_commandtable *node_to_fill)
{
	if (node_to_fill->is_a_command == 0)
	{
		node_to_fill->is_a_command = 2;
		free(node_to_fill->command);
		node_to_fill->command = 0;
		if (node_to_fill->self_input_fd != -1)
			close(node_to_fill->self_input_fd);
		if (node_to_fill->self_output_fd != -1)
			close(node_to_fill->self_output_fd);
	}
}

t_commandtable	*get_node_to_fill(t_commandtable *current_node)
{
	t_commandtable	*node_to_fill;

	current_node = get_table_after_pipe(current_node);
	node_to_fill = current_node;
	while (current_node && current_node->pipe == 0)
	{
		if (current_node->is_a_command == 1)
		{
			node_to_fill = current_node;
			break ;
		}
		if (current_node->next)
			current_node = current_node->next;
		else
			break ;
	}
	if (current_node->is_a_command)
		node_to_fill = current_node;
	get_node_to_fill_compliment(node_to_fill);
	return (node_to_fill);
}
