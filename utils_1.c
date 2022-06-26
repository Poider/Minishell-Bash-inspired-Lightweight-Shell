/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:26:24 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:28:09 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var)
{
	char	*var_value;

	var_value = getenv(var);
	free(var);
	return (var_value);
}

int	whitespaces(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
		|| c == '\r' || c == '\v' || c == '\f');
}

int	is_full_of_whitespaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!whitespaces(line[i]))
			return (0);
		i++;
	}
	return (1);
}

