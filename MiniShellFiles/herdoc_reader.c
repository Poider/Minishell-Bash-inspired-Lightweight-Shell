/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:34:15 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 18:38:04 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herdoc_condition(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (-2);
}

char	*expand_herdoc(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			line = dollar_check(&i, g_v_lines, line);
		else if (whitespaces(line[i]))
			line = delete_spaces(line, i);
		else if (line[i] == '*')
			line[i] = (char)-1;
		i++;
	}
	return (line);
}

int	make_herdoc_pipe(char *limiter, int permission)
{
	t_iters10	iters;

	iters.newliney = '\n';
	pipe(iters.fd);
	while (1)
	{
		iters.line = readline("heredoc>> ");
		if (!iters.line)
			break ;
		if (permission == -1)
			iters.line = expand_herdoc(iters.line);
		if (!ft_strncmp(iters.line, limiter, max(ft_strlen(limiter),
					ft_strlen(iters.line))))
		{
			free(iters.line);
			break ;
		}
		write(iters.fd[1], iters.line, ft_strlen(iters.line));
		write(iters.fd[1], &iters.newliney, 1);
		if (iters.line)
			free(iters.line);
	}
	close(iters.fd[1]);
	return (iters.fd[0]);
}
