/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:40:01 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:51:38 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arguments	*get_last_argument(t_arguments *argument)
{
	if (argument)
		while (argument->next != 0)
			argument = argument->next;
	return (argument);
}


t_commandtable	*late_command(int pipe, int redirection)
{
	t_commandtable	*command_table;

	initialize_command_table_node(g_v_lines);
	command_table = get_last_command_line(g_v_lines->command_table);
	command_table->pipe = pipe;
	command_table->redirections = redirection;
	command_table->is_a_command = 1;
	return (command_table);
}

int	token_stop(char *line, int i)
{
	while (whitespaces(line[i]))
		i++;
	if (line[i] == 34 || line[i] == 39)
		return (0);
	else
		return (1);
}

t_commandtable	*fill_arg_c(t_commandtable *late_table,
		t_commandtable *command_table, char *token)
{
	late_table = late_command(command_table->pipe, command_table->redirections);
	late_table->command = token;
	command_table->pipe = 0;
	command_table->redirections = 0;
	g_v_lines->got_command_yet = 1;
	return (late_table);
}

void	fill_arguments(t_commandtable *command_table, char *line, int *index)
{
	int				i;
	int				j;
	char			*token;
	t_arguments		*current_argument;
	t_commandtable	*late_table;

	i = *index;
	while (1)
	{
		j = token_stop(line, i);
		token = clean_token(line, &i);
		if (token[0] == 0 && j)
		{
			free(token);
			break ;
		}
		if (g_v_lines->got_command_yet == 0)
		{
			late_table = fill_arg_c(late_table, command_table, token);
			continue ;
		}
		initialize_argument_node(command_table);
		current_argument = get_last_argument(command_table->argument);
		current_argument->arg = token;
	}
}