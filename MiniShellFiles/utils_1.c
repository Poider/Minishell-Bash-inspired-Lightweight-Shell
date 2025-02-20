/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:26:24 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:08:40 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_getenv(char *var)
{
	t_list	*head;
	char	*result;

	result = NULL;
	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(var, head->key, max(ft_strlen(var), \
			ft_strlen(head->key))))
			result = head->value;
		head = head->next;
	}
	return (result);
}

char	*get_var(char *var)
{
	char	*var_value;

	var_value = _getenv(var);
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
