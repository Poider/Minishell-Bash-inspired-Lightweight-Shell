/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:10 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:58:46 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ct(t_line_processing_history *g_v_lines)
{
	t_commandtable *c_table;
	t_arguments *argi;
	c_table = g_v_lines->command_table;
	fflush(stdout);
	while (c_table)
	{
		printf("is command : %d, is a file_toWrite %d, is_herdoc %d, is append %d,file_toRead%d\n", c_table->is_a_command, c_table->is_a_file, c_table->is_heredoc, c_table->is_a_file_a, c_table->is_a_file_r);
		printf("command: {%s}\n", c_table->command);
		printf("limiter: {%s}\n", c_table->limiter);
		printf("is next pipe:%d, is next redirection:%d\n", c_table->pipe, c_table->redirections);
		printf("input_fd : %d,output_fd : %d\n", c_table->input_fd, c_table->output_fd);
		printf("arguements: \n");
		argi = c_table->argument;
		while (argi != 0)
		{
			printf(" arg : {%s}\n", argi->arg);
			argi = argi->next;
		}
		printf(" \n\n\n\n");
		c_table = c_table->next;
	}
	fflush(stdout);
}


void	execute_built_in(int built_in_number)
{
	printf("execute built_in\n");
}


int	parse(t_line_processing_history *g_v_lines)
{
	if (!expandline(g_v_lines))
		return (0);
	return (1);
}

int	processline(t_line_processing_history *g_v_lines)
{
	int	parse_success;

	g_v_lines->trimmed_line = ft_strtrim(g_v_lines->entered_line, " 		");
	if (!ft_strncmp(g_v_lines->trimmed_line, "exit", \
			max(ft_strlen(g_v_lines->trimmed_line), 4)))
	{
		handle_exit();
	}
	parse_success = parse(g_v_lines);
	if (parse_success)
		parse_success = process_command_table(g_v_lines);
	if (parse_success)
	{
		print_ct(g_v_lines);
		// syntax_check();
		// execute(g_v_lines);//talk bout if theres smth that needs to go back here in the parsin
	}
	return (1);
}

int	readline_loop(t_line_processing_history *g_v_lines)
{
	while (1)
	{
		handle_signals();
		g_v_lines->entered_line = readline("bash tsetta -0.1 $ ");
		if (!g_v_lines->entered_line)
			handle_exit();
		if (!is_full_of_whitespaces(g_v_lines->entered_line))
		{
			add_history(g_v_lines->entered_line);
			processline(g_v_lines);
		}
		if (g_v_lines->parent_id != 0)
			wait(NULL);
		else
		{
			close_fds(g_v_lines->command_table);
			free_all(g_v_lines);
			free_env(g_v_lines->env_vars);
			return (1);
		}
		free_all(g_v_lines);
	}
}

int	main(int argc, char **argv, char **env)
{
	struct termios	oldtio;
	struct termios	newtio;

	g_v_lines = malloc(sizeof(t_line_processing_history));
	initialize_v_lines(g_v_lines, env);
	handle_signals();
	tcgetattr(0, &oldtio);
	g_v_lines->terminal_settings = oldtio;
	oldtio.c_lflag &= ~ICANON;
	oldtio.c_lflag &= ECHO;
	tcsetattr(0, TCSANOW, &oldtio);
	return (readline_loop(g_v_lines));
	return (1);
}
