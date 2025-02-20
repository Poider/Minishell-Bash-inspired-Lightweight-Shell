/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:06:57 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:21:44 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*number_to_redirection(int c)
{
	if (c == 1)
		return (ft_strdup(">"));
	else if (c == 2)
		return (ft_strdup(">>"));
	else if (c == 3)
		return (ft_strdup("<"));
	else if (c == 4)
		return (ft_strdup("<<"));
	else if (c == 10)
		return (ft_strdup("|"));
	else
		return (0);
}

int	reached_a_redirection_or_end(char c)
{
	if (c == '|')
		return (10);
	if (c == '>')
		return (1);
	if (c == '<')
		return (3);
	if (c == '\0')
		return (69);
	return (0);
}

int	pipe_redirection(char c, char after_c)
{
	if (c == '|')
		return (10);
	else if (c == '>')
	{
		if (after_c == '>')
			return (2);
		else
			return (1);
	}
	else if (c == '<')
	{
		if (after_c == '<')
			return (4);
		else
			return (3);
	}
	return (0);
}

int	check_previous_redirection(char *line, int start)
{
	int	prev;

	if (start >= 2)
	{
		prev = reached_a_redirection_or_end(line[start - 1]);
		if (reached_a_redirection_or_end(line[start - 2]) == prev)
			return (prev + 1);
		else
			return (prev);
	}
	else if (start == 1)
	{
		return (reached_a_redirection_or_end(line[start - 1]));
	}
	else
		return (0);
}
