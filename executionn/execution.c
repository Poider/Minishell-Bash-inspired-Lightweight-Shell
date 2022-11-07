/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:30 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:39 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_commande_and_built_in_pipe(t_execute_var	*var)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(var->fd[0]);
	if (var->command_table->input_fd)
		dup2(var->command_table->input_fd, 0);
	else if (var->pipe_save != 0)
		dup2(var->pipe_save, 0);
	if (var->command_table->output_fd >= 3)
		var->out = var->command_table->output_fd;
	else if (var->command_table->next == 0)
		var->out = 1;
	dup2(var->out, 1);
	var->args = args_to_table(var->command_table->argument);
	if (var->built_in_number && g_v_lines->commands_number != 1)
		execute_built_in_child(var->built_in_number, \
			var->command_table->argument);
	else if (!var->built_in_number)
	{
		var->can_access = commande_with_path(g_v_lines->command_table);
		correct_access(var->command_table);
	}
}

void	exit_signals(t_execute_var *var)
{
	var->i = 0;
	while (var->i < g_v_lines->commands_number)
	{
		var->j = 0;
		waitpid(g_v_lines->process_id[var->i], &var->j, 0);
		if (WIFSIGNALED(var->j))
			g_v_lines->exit_status = 128 + WTERMSIG(var->j);
		else
			g_v_lines->exit_status = WEXITSTATUS(var->j);
		var->i++;
	}
}

void	initial_var(t_execute_var *var)
{
	var->pipe_save = 0;
	var->command_table = g_v_lines->command_table;
	g_v_lines->commands_number = number_of_commands(var->command_table);
	g_v_lines->process_id = malloc(sizeof(int) * g_v_lines->commands_number);
}

void	close_fd(t_execute_var *var)
{
	if (var->pipe_save != 0 && var->pipe_save != 1)
		close(var->pipe_save);
	close(var->fd[1]);
	var->pipe_save = var->fd[0];
	var->command_table = var->command_table->next;
	if (var->command_table == NULL)
		close(var->pipe_save);
}

int	execute(t_line_processing_history *g_v_lines)
{
	t_execute_var	var;

	initial_var(&var);
	signal(SIGINT, SIG_IGN);
	while (var.command_table != 0)
	{
		pipe(var.fd);
		var.out = var.fd[1];
		if (var.command_table->command)
		{
			var.built_in_number = built_in_check(var.command_table->command);
			if (!(var.built_in_number && g_v_lines->commands_number == 1))
			{
				g_v_lines->process_id[g_v_lines->iterator++] = fork();
				if (g_v_lines->process_id[g_v_lines->iterator - 1] == 0)
				{
					execute_commande_and_built_in_pipe(&var);
					return (1);
				}
			}
		}
		close_fd(&var);
	}
	exit_signals(&var);
	return (1);
}
