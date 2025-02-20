/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:05:45 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 13:31:36 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quote(char *token, int *start_quote_position)
{
	t_iters7	iters;

	iters.i = *start_quote_position;
	iters.quote_type = token[iters.i];
	iters.i++;
	iters.side_1 = ft_substr(token, 0, *start_quote_position);
	while (token[iters.i] != iters.quote_type)
		iters.i++;
	iters.middle_stuff = ft_substr(token, *start_quote_position + 1,
			iters.i - 1 - *start_quote_position);
	iters.side_2 = ft_substr(token, iters.i + 1, ft_strlen(token));
	iters.temp = ft_strjoin(iters.side_1, iters.middle_stuff);
	token = ft_strjoin(iters.temp, iters.side_2);
	free(iters.side_1);
	free(iters.side_2);
	free(iters.middle_stuff);
	free(iters.temp);
	*start_quote_position = iters.i - 2;
	return (token);
}

void	unclosed_quotes(void)
{
	g_v_lines->failure = 1;
	printf("You have an unclosed quote\n");
}

char	*process_double_quotes(char *line, int *end_quote,
	t_line_processing_history *g_v_lines)
{
	int	i;

	i = *end_quote + 1;
	while (line[i] != 34)
	{
		if (line[i] == '$')
			line = dollar_check(&i, g_v_lines, line);
		if (!line)
		{
			return (0);
		}
		if (line[i] == '\0')
		{
			free(line);
			unclosed_quotes();
			return (0);
		}
		if (line[i] == 34)
			break ;
		i++;
	}
	*end_quote = i;
	return (line);
}

char	*process_single_quotes(char *line, int *end_quote,
	t_line_processing_history *g_v_lines)
{
	int	i;

	(void)(*g_v_lines);
	i = *end_quote + 1;
	while (line[i] != 39)
	{
		if (line[i] == '\0')
		{
			free(line);
			unclosed_quotes();
			return (0);
		}
		i++;
	}
	*end_quote = i;
	return (line);
}

char	*process_quotes(int *index,
				t_line_processing_history *g_v_lines, char *line)
{
	int	i;

	i = *index;
	if (line[i] == 34)
		line = process_double_quotes(line, &i, g_v_lines);
	else if (line[i] == 39)
		line = process_single_quotes(line, &i, g_v_lines);
	*index = i;
	return (line);
}
