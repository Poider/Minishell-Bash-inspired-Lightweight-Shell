/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:47:23 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:02:09 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in_check_compliment(char *line)
{
	if (!ft_strncmp("echo", line, max(ft_strlen(line), \
				ft_strlen("echo"))) || !ft_strncmp("ECHO", line, \
				max(ft_strlen(line), ft_strlen("ECHO"))))
		return (17);
	else
		return (0);
}

int	built_in_check(char *line)
{
	if (!ft_strncmp("cd", line, max(ft_strlen(line), ft_strlen("cd"))) \
		|| !ft_strncmp("CD", line, max(ft_strlen(line), ft_strlen("CD"))))
		return (11);
	else if (!ft_strncmp("pwd", line, max(ft_strlen(line), ft_strlen("pwd"))) \
		|| !ft_strncmp("PWD", line, max(ft_strlen(line), ft_strlen("PWD"))))
		return (12);
	else if (!ft_strncmp("export", line, max(ft_strlen(line),
				ft_strlen("export"))) && ft_strncmp("EXPORT", \
		line, max(ft_strlen(line), ft_strlen("EXPORT"))))
		return (13);
	else if (!ft_strncmp("unset", line, max(ft_strlen(line), ft_strlen
				("unset"))) \
		&& ft_strncmp("UNSET", line, max(ft_strlen(line), ft_strlen("UNSET"))))
		return (14);
	else if (!ft_strncmp("exit", line, max(ft_strlen(line), ft_strlen("exit"))) \
		&& ft_strncmp("EXIT", line, max(ft_strlen(line), ft_strlen("EXIT"))))
		return (15);
	else if (!ft_strncmp("env", line, max(ft_strlen(line), ft_strlen("env"))) \
		|| !ft_strncmp("ENV", line, max(ft_strlen(line), ft_strlen("ENV"))))
		return (16);
	else
		return (built_in_check_compliment(line));
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
