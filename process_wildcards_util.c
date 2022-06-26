/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wildcards_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:43:26 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:43:27 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_arg_node(t_commandtable *command_table,
			t_arguments *arg_to_delete)
{
	t_arguments	*previous;
	t_arguments	*next;

	next = arg_to_delete->next;
	previous = arg_to_delete->previous;
	if (arg_to_delete->arg)
		free(arg_to_delete->arg);
	free(arg_to_delete);
	if (previous)
		previous->next = next;
	else
		command_table->argument = next;
	if (next)
		next->previous = previous;
}

