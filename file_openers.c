/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_openers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:33:33 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 17:07:18 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_opener_condition(int r_fd, int w_fd, int *read_fd, int *write_fd)
{
	if (r_fd)
		*read_fd = r_fd;
	if (w_fd)
		*write_fd = w_fd;
}

int	file_opener(int permission, char *file_name, int *read_fd, int *write_fd)
{
	int	r_fd;
	int	w_fd;

	r_fd = 0;
	w_fd = 0;
	if (permission == 1)
		r_fd = open(file_name, O_RDONLY);
	else if (permission == 2)
		w_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (permission == 3)
		w_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (permission == 0 || permission == -1)
		r_fd = make_herdoc_pipe(file_name, permission);
	if (r_fd == -1 || w_fd == -1)
	{
		g_v_lines->failure = 1;
		printf("No such file or directory \n");
		exit(1);
	}
	else if (r_fd == -2)
		return (0);
	file_opener_condition(r_fd, w_fd, read_fd, write_fd);
	return (1);
}
