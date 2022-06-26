/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:48:19 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:03:17 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_envirement_vars(t_line_processing_history *g_v_lines,
	char **env)
{
	int		env_vars_count;
	char	**array;
	int		i;

	i = 0;
	env_vars_count = 0;
	while (env[env_vars_count])
		env_vars_count++;
	g_v_lines->env_vars = malloc(sizeof(char *) * (env_vars_count + 1));
	array = g_v_lines->env_vars;
	while (i < env_vars_count)
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	array[i] = 0;
}

int	initialize_v_lines(t_line_processing_history *g_v_lines, char **env)
{
	g_v_lines->exit_status = 0;
	g_v_lines->command_table = 0;
	g_v_lines->is_next_a_command = 0;
	g_v_lines->iterator = 0;
	g_v_lines->process_id = 0;
	g_v_lines->parent_id = 11;
	g_v_lines->got_command_yet = 0;
	g_v_lines->entered_line = 0;
	g_v_lines->expanded_line = 0;
	g_v_lines->trimmed_line = 0;
	g_v_lines->dollar_processed = 0;
	duplicate_envirement_vars(g_v_lines, env);
	return (1);
}

void	null_command_table_arguments(t_commandtable *command_table)
{
	command_table->argument = 0;
	command_table->command = 0;
	command_table->is_a_file_a = 0;
	command_table->is_a_file_r = 0;
	command_table->limiter = 0;
	command_table->is_a_command = 0;
	command_table->is_a_file = 0;
	command_table->is_heredoc = 0;
	command_table->limiter = 0;
	command_table->pipe = 0;
	command_table->redirections = 0;
	command_table->input_fd = 0;
	command_table->output_fd = 1;
	command_table->self_input_fd = -1;
	command_table->self_output_fd = -1;
}

void	initialize_command_infos(t_commandtable *command_table)
{
	null_command_table_arguments(command_table);
	command_table->command = 0;
	command_table->argument = 0;
	command_table->is_a_command = 0;
	command_table->is_a_file = 0;
	command_table->is_heredoc = 0;
	command_table->is_a_file_a = 0;
	command_table->is_a_file_r = 0;
	command_table->limiter = 0;
	command_table->pipe = 0;
	command_table->redirections = 0;
	command_table->next = 0;
}

int	initialize_command_table_node(t_line_processing_history *g_v_lines)
{
	t_commandtable	*command_table;
	t_commandtable	*temp;

	if (!g_v_lines->command_table)
	{
		g_v_lines->command_table = malloc(sizeof(t_commandtable));
		command_table = g_v_lines->command_table;
		command_table->previous = 0;
		initialize_command_infos(command_table);
	}
	else
	{
		temp = get_last_command_line(g_v_lines->command_table);
		command_table = malloc(sizeof(t_commandtable));
		temp->next = command_table;
		command_table->previous = temp;
		initialize_command_infos(command_table);
	}
	return (1);
}
