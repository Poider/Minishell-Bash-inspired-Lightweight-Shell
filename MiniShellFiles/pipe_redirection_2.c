/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:15:12 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:21:28 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herdoc_error(char *line, int i)
{
	i = i + 2;
	while (whitespaces(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		g_v_lines->failure = 1;
		printf("Parse error, nothing or newline after redirection\n");
		return (1);
	}
	return (0);
}

int	find_duplicate_redirections_compliment_0(char *line)
{
	free(line);
	g_v_lines->failure = 1;
	printf("multiple redirections\n");
	return (1);
}

int	find_duplicate_redirections_compliment_1(t_iters3 iters, int i)
{
	if (iters.redirection == 2 || iters.redirection == 4)
			i++;
	return (i);
}

int	find_duplicate_redirections(char *line, int i)
{
	t_iters3	iters;

	iters.j = 0;
	while (line[i] && line[i] != 34 && line[i] != 39)
	{
		iters.redirection = pipe_redirection(line[i], line[i + 1]);
		i = find_duplicate_redirections_compliment_1(iters, i);
		if (iters.redirection)
		{
			iters.j = i + 1;
			while (whitespaces(line[iters.j]))
				iters.j++;
			iters.previous_redirection = reached_a_redirection_or_end
				(line[iters.j]);
			if (iters.redirection == 10)
			{
				if (iters.previous_redirection == 10)
					return (find_duplicate_redirections_compliment_0(line));
			}
			else if (iters.previous_redirection && line[iters.j] != 0)
				return (find_duplicate_redirections_compliment_0(line));
		}
		i++;
	}
	return (0);
}
