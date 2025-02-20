/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:50:13 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 14:51:42 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_table(t_commandtable *command_table)
{
	t_commandtable	*table;

	while (command_table)
	{
		table = command_table->next;
		free_command_table_content(command_table);
		free(command_table);
		command_table = table;
	}
}

void	free_all(t_line_processing_history *g_v_lines)
{
	free_command_table(g_v_lines->command_table);
	free_lines(g_v_lines);
	null_lines(g_v_lines);
}

void	free_env_list(void)
{
	t_list	*head;
	t_list	*temp;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		temp = head;
		free(head->key);
		free(head->value);
		head = head->next;
		free(temp);
	}
}
