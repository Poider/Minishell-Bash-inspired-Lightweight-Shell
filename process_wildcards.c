/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:22:24 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:09:21 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == -1)
			return (1);
		i++;
	}
	return (0);
}

void	change_back_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = '*';
		i++;
	}
}

int	handle_command_wildcard(t_commandtable *command_table)
{
	t_arguments	*matched_args;
	t_arguments	*next;
	int			i;

	i = 0;
	matched_args = match_with_directory(command_table->command);
	if (!matched_args)
	{
		change_back_wildcard(command_table->command);
		return (0);
	}
	command_table->command = matched_args->arg;
	matched_args = matched_args->next;
	if (matched_args)
	{
		matched_args->previous = 0;
		next = command_table->argument;
		command_table->argument = matched_args;
		matched_args = get_last_argument(matched_args);
		matched_args->next = next;
	}
	return (1);
}

t_arguments	*handle_args_wildcard(t_commandtable *command_table,
			t_arguments *args)
{
	t_arguments	*next;
	t_arguments	*previous;
	t_arguments	*matched_args;

	matched_args = match_with_directory(args->arg);
	if (!matched_args)
	{
		change_back_wildcard(args->arg);
		return (args);
	}
	next = args->next;
	previous = args->previous;
	delete_arg_node(command_table, args);
	if (previous)
		previous->next = matched_args;
	else
		command_table->argument = matched_args;
	matched_args->previous = previous;
	matched_args = get_last_argument(matched_args);
	matched_args->next = next;
	return (next);
}

int	process_wildcards(t_commandtable *command_table)
{
	t_arguments	*args;

	while (command_table)
	{
		if (command_table->command)
			if (check_wildcard(command_table->command))
				handle_command_wildcard(command_table);
		args = command_table->argument;
		while (args)
		{
			if (check_wildcard(args->arg))
			{
				args = handle_args_wildcard(command_table, args);
				continue ;
			}
			args = args->next;
		}
		command_table = command_table->next;
	}
	return (1);
}
