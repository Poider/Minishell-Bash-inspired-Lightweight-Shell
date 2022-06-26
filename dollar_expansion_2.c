/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:04:22 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:04:46 by mel-amma         ###   ########.fr       */
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
				g_v_lines->exit_status = 1;
				printf("ambiguous redirect\n");
				return (1);
			}
		}
	}
	return (0);
}

char	*expand_dollar(char *line, int var_start, int var_len, int type)
{
	char	*temp_joined;
	char	*joined;
	char	*side_1;
	char	*side_2;
	char	*var_value;

	if (var_len == 0)
		var_len = 1;
	side_1 = ft_substr(line, 0, var_start - 1);
	side_2 = ft_substr(line, var_start + var_len, ft_strlen(line));
	if (type == 0)
		var_value = get_var(ft_substr(line, var_start, var_len));
	else if (type == 1)
		var_value = ft_itoa(g_v_lines->exit_status);
	temp_joined = ft_strjoin(side_1, var_value);
	joined = ft_strjoin(temp_joined, side_2);
	free(temp_joined);
	free(side_1);
	free(side_2);
	if (type == 0 && ft_strlen(var_value) == 0)
		if (check_file_expansion_named(line, var_start - 2))
			return (0);
	free(line);
	return (joined);
}