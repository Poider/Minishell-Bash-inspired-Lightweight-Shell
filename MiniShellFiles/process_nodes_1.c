/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nodes_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:38:33 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:04:58 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commandtable	*get_last_command_line(t_commandtable *command_table)
{
	while (command_table->next != 0)
		command_table = command_table->next;
	return (command_table);
}

void	clean_token_compliment(t_iters6 *iters, int *i, int *j, int *len)
{
	char	*tok;
	char	*tem;

	tok = iters->token;
	tem = iters->temp;
	while (!whitespaces(tok[*(i)]) && tok[*(i)])
	{
		if (tok[*(i)] == 34 || tok[*(i)] == 39)
		{
			tem = tok;
			tok = delete_quote(tok, i);
			free(tem);
			*j = *j + 1;
		}
		*i = *i + 1;
		*len = *len + 1;
	}
	iters->temp = tem;
	iters->token = tok;
}

char	*clean_token(char *line, int *iteration_position)
{
	t_iters6	iters;
	int			len;
	int			i;
	int			j;

	iters.token = ft_strdup(line);
	j = 0;
	iters.temp = NULL;
	i = *iteration_position;
	while (whitespaces(iters.token[i]) && iters.token[i])
		i++;
	*iteration_position = i;
	clean_token_compliment(&iters, &i, &j, &len);
	iters.temp = iters.token;
	iters.token = ft_substr(iters.token, *iteration_position,
			i - *iteration_position);
	free(iters.temp);
	*iteration_position = i + 2 * j;
	return (iters.token);
}
