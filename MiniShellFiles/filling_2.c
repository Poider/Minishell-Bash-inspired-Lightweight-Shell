/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:24:32 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 17:26:14 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_exists(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	fill_limiter(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->quote_in_limiter = quote_exists(line);
	command_table->limiter = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}
