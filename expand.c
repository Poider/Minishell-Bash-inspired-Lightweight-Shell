#include "minishell.h"

char	*delete_spaces(char *line, int start_eliminating)
{
	char	*cleared_line;
	char	*side_1;
	char	*side_2;
	int		i;

	i = start_eliminating;
	while (whitespaces(line[i]))
		i++;
	side_2 = ft_substr(line, i, ft_strlen(line));
	i = 1;
	if (!ft_strlen(side_2))
		i = 0;
	side_1 = ft_substr(line, 0, start_eliminating + i);
	cleared_line = ft_strjoin(side_1, side_2);
	free(line);
	free(side_1);
	free(side_2);
	return (cleared_line);
}

char	*expandline_compliment_0(char *line, int *index)
{
	int	i;

	i = *index;
	if (line[i] == '$')
		line = dollar_check(&i, g_v_lines, line);
	else if (line[i] == 34 || line[i] == 39)
		line = process_quotes(&i, g_v_lines, line);
	else if (whitespaces(line[i]))
		line = delete_spaces(line, i);
	else if (line[i] == '*')
		line[i] = (char)-1;
	*index = i;
	return (line);
}

int	expandline_compliment_1(int redirection, int i)
{
	if (redirection == 10)
		g_v_lines->got_command_yet = 0;
	if (redirection == 4)
		i++;
	return (i);
}

int	expandline_compliment(t_iters4 *t)
{
	while (t->line[++(t->i)])
	{
		t->redirection = pipe_redirection(t->line[t->i], t->line[t->i + 1]);
		if (t->redirection == 4)
			if (herdoc_error(t->line, t->i))
				return (0);
		t->line = expandline_compliment_0(t->line, &(t->i));
		if (!t->line)
			return (0);
		if (find_duplicate_redirections(t->line, t->i))
			return (0);
		if (t->redirection)
		{
			t->line = check_redirection_error(t->line, t->i, t->redirection);
			if (!t->line)
				return (0);
			if (!expanded_line_2_command_table(g_v_lines, get_last_pipe
					(&(t->flag), t->line), t->redirection, ft_strdup(t->line)))
				return (0);
		}
		t->i = expandline_compliment_1(t->redirection, t->i);
		if (!t->line[t->i])
			break ;
	}
	return (1);
}

int	expandline(t_line_processing_history *g_v_lines)
{
	t_iters4	iters;

	iters.i = -1;
	iters.flag = 0;
	iters.line = ft_strdup(g_v_lines->trimmed_line);
	if (start_error(iters.line))
		return (0);
	if (!expandline_compliment(&iters))
		return (0);
	if (!expanded_line_2_command_table(g_v_lines, get_last_pipe(&(iters.flag),
				iters.line), 0, ft_strdup(iters.line)))
		return (0);
	g_v_lines->expanded_line = iters.line;
	return (1);
}