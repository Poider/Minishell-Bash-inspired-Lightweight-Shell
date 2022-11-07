/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:57:38 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:03:12 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_argument_node(t_commandtable *command_table)
{
	t_arguments	*argument;
	t_arguments	*temp;

	if (!command_table->argument)
	{
		command_table->argument = malloc(sizeof(t_arguments));
		argument = command_table->argument;
		argument->previous = 0;
		argument->arg = 0;
		argument->next = 0;
	}
	else
	{
		temp = get_last_argument(command_table->argument);
		argument = malloc(sizeof(t_arguments));
		temp->next = argument;
		argument->previous = temp;
		argument->arg = 0;
		argument->next = 0;
	}
}
