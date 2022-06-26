/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:47:23 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:47:36 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_check(char *line)
{
	if (!ft_strncmp("cd", to_lower(line), max(ft_strlen(line), ft_strlen(""))))
		return (11);
	else if (!ft_strncmp("export", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (13);
	else if (!ft_strncmp("unset", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (14);
	else if (!ft_strncmp("exit", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (15);
	else
		return (0);
}

int	is_built_in(t_line_processing_history *g_v_lines)
{
	t_commandtable	*command_table;
	t_commandtable	*command;
	int				i;
	int				is_built_in;

	is_built_in = 0;
	i = 0;
	command_table = g_v_lines->command_table;
	while (command_table)
	{
		if (command_table->is_a_command == 1)
		{
			command = command_table;
			i++;
		}
		command_table = command_table->next;
	}
	if (i == 1)
		is_built_in = built_in_check(command->command);
	return (is_built_in);
}