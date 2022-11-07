/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:03:02 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 15:02:11 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_check_compliment_0(char *line)
{
	free(line);
	g_v_lines->failure = 1;
	printf("Insert process ID of current bash instance here,\
but Im not supposed to handle it :D\n");
	return (0);
}

void	dollar_check_compliment_1(char *line, int i, int len)
{
	if (g_v_lines->dollar_processed)
		free(g_v_lines->dollar_processed);
	g_v_lines->dollar_processed = expand_dollar(line, i + 1, len, 0);
}

char	*dollar_check_compliment_2(char *line, int j)
{
	if (g_v_lines->dollar_processed)
		free(g_v_lines->dollar_processed);
	g_v_lines->dollar_processed = expand_dollar(line, j, 1, 1);
	return (ft_strdup(g_v_lines->dollar_processed));
}

void	dollar_check_compliment_3(char *line, int j, int *len)
{
	if (line[j] <= 48 || line[j] >= 57)
		while (ft_isalnum(line[j++]))
			*len = *len + 1;
}

char	*dollar_check(int *index,
		t_line_processing_history *g_v_lines, char *line)
{
	t_iters1	iters;

	iters.len = 0;
	iters.i = *index;
	if (line[iters.i] == '$')
	{
		iters.j = iters.i + 1;
		if (ft_isalnum(line[iters.j]) || line[iters.j] == '$')
		{
			if (line[iters.j] == '$')
				return (dollar_check_compliment_0(line));
			else
			{
				dollar_check_compliment_3(line, iters.j, &(iters.len));
				dollar_check_compliment_1(line, iters.i, iters.len);
				if (!g_v_lines->dollar_processed)
					return (0);
				line = ft_strdup(g_v_lines->dollar_processed);
			}
		}
		else if (line[iters.j] == '?')
			line = dollar_check_compliment_2(line, iters.j);
	}
	*index = iters.i;
	return (line);
}
