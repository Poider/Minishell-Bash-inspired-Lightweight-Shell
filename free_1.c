/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:46:43 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 11:49:58 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_lines(t_line_processing_history *g_v_lines)
{
	if (g_v_lines->process_id)
		free(g_v_lines->process_id);
	free(g_v_lines->entered_line);
	free(g_v_lines->expanded_line);
	free(g_v_lines->trimmed_line);
	free(g_v_lines->dollar_processed);
	return (1);
}

int	null_lines(t_line_processing_history *g_v_lines)
{
	g_v_lines->got_command_yet = 0;
	g_v_lines->entered_line = 0;
	g_v_lines->expanded_line = 0;
	g_v_lines->trimmed_line = 0;
	g_v_lines->dollar_processed = 0;
	g_v_lines->is_next_a_command = 0;
	g_v_lines->command_table = 0;
	g_v_lines->iterator = 0;
	g_v_lines->process_id = 0;
	g_v_lines->commands_number = 0;
	return (1);
}

void	free_env(char **arr)
{
	int	i;
	int	env_vars_count;

	env_vars_count = 0;
	i = 0;
	while (arr[env_vars_count])
		env_vars_count++;
	while (i < env_vars_count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_arguments(t_arguments *argument)
{
	t_arguments	*arg;

	while (argument)
	{
		arg = argument->next;
		if (argument->arg)
		{
			free(argument->arg);
			argument->arg = 0;
		}
		free(argument);
		argument = arg;
	}
}

void	free_command_table_content(t_commandtable *command_table)
{
	if (command_table->command)
		free(command_table->command);
	if (command_table->argument)
		free_arguments(command_table->argument);
	if (command_table->limiter)
		free(command_table->limiter);
	null_command_table_arguments(command_table);
}
