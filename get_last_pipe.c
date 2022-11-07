/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:08:12 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 14:51:20 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_last_pipe_compliment(int *flag, int *last_start_position)
{
	if (*flag == 0)
	{
		*last_start_position = 0;
		*flag = 1;
	}
}

int	g_l_p_c_0(t_iters2 iters, int last_start_position)
{
	if (iters.redirection_number == 4)
		last_start_position++;
	last_start_position++;
	return (last_start_position);
}

int	get_last_pipe(int *flag, char *line)
{
	static int	last_start_position;
	t_iters2	iters;

	get_last_pipe_compliment(flag, &last_start_position);
	if (last_start_position == -1)
		return (-1);
	iters.start_position = last_start_position;
	if (line[last_start_position])
	{
		iters.redirection_number = pipe_redirection(line[last_start_position],
				line[last_start_position + 1]);
		while (!iters.redirection_number && line[last_start_position + 1])
		{
			last_start_position++;
			iters.redirection_number = pipe_redirection
				(line[last_start_position], line[last_start_position + 1]);
		}
		if (line[last_start_position + 1] == '\0')
			last_start_position = -1;
		else
			last_start_position = g_l_p_c_0(iters, last_start_position);
	}
	return (iters.start_position);
}
