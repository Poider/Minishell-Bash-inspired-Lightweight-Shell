/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:29:20 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:31:26 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_error(char *line)
{
	int	i;

	i = 0;
	while (whitespaces(line[i]))
		i++;
	if (line[i] == '|')
	{
		g_v_lines->exit_status = 1;
		printf("Error: Why u be startin shit with a pipe\n");
		return (1);
	}
	return (0);
}

char	*redirection_error(char *line, int i)
{
	char	*side_2;
	char	*temp;

	side_2 = NULL;
	if (check_pipe_error(line, i + 1))
	{
		g_v_lines->exit_status = 1;
		free(line);
		printf("Parse error, nothing or newline after redirection\n");
		return (0);
	}
	return (line);
}

char	*check_redirection_error(char *line, int i, int redirection)
{
	if (redirection == 10)
		line = pipe_error(line, i);
	else if (redirection >= 1 && redirection <= 4)
		line = redirection_error(line, i);
	return (line);
}

char	*pipe_error(char *line, int i)
{
	char	*side_2;
	char	*temp;

	side_2 = NULL;
	if (check_pipe_error(line, i + 1))
	{
		while (!side_2 || is_full_of_whitespaces(side_2))
			side_2 = readline("pipe>");
		temp = line;
		line = ft_strjoin(line, side_2);
		free(temp);
		free(side_2);
		return (line);
	}
	return (line);
}

int	check_pipe_error(char *line, int i)
{
	while (whitespaces(line[i]) && line[i])
		i++;
	if (line[i])
		return (0);
	else
		return (1);
}
