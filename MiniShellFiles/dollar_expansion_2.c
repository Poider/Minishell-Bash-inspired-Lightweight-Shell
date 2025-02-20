/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:04:22 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:24:57 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_expansion_named(char *line, int i)
{
	if (i > 0)
	{
		while (whitespaces(line[i]))
			i--;
		if (i > 0)
		{
			if (reached_a_redirection_or_end(line[i]))
			{
				free(line);
				g_v_lines->failure = 1;
				printf("ambiguous redirect\n");
				return (1);
			}
		}
	}
	return (0);
}

static void	expand_dollar_freeing(int type, char *var_value, \
			char *temp_joined, char *side_1)
{
	if (type == 1)
		free(var_value);
	free(temp_joined);
	free(side_1);
}

char	*expand_dollar(char *line, int var_start, int var_len, int type)
{
	t_iters8	iter;

	if (var_len == 0)
		var_len = 1;
	iter.side_1 = ft_substr(line, 0, var_start - 1);
	iter.side_2 = ft_substr(line, var_start + var_len, ft_strlen(line));
	if (type == 0)
		iter.var_value = get_var(ft_substr(line, var_start, var_len));
	else if (type == 1)
		iter.var_value = ft_itoa(g_v_lines->exit_status);
	iter.temp_joined = ft_strjoin(iter.side_1, iter.var_value);
	iter.joined = ft_strjoin(iter.temp_joined, iter.side_2);
	expand_dollar_freeing(type, iter.var_value, \
			iter.temp_joined, iter.side_1);
	free(iter.side_2);
	if (type == 0 && ft_strlen(iter.var_value) == 0)
	{
		if (check_file_expansion_named(line, var_start - 2))
		{
			free(iter.joined);
			return (0);
		}
	}
	free(line);
	return (iter.joined);
}
