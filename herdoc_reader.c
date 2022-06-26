/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:34:15 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:34:30 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herdoc_condition(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (-2);
}

int	make_herdoc_pipe(char *limiter)
{
	int		fd[2];
	char	*line;
	char	newliney;

	newliney = '\n';
	pipe(fd);
	line = "$^(!)g1?e4t_2i3n";
	while (1)
	{
		line = readline("heredoc>> ");
		if (!line)
			return (herdoc_condition(fd));
		if (!ft_strncmp(line, limiter, max(ft_strlen(limiter),
					ft_strlen(line))))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], &newliney, 1);
		if (line)
			free(line);
	}
	close(fd[1]);
	return (fd[0]);
}