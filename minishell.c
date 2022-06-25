/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:10 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/25 17:27:29 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line_processing_history	*g_v_lines;

int	free_lines(t_line_processing_history *g_v_lines)
{
	if (g_v_lines->process_id)
		free(g_v_lines->process_id);
	free(g_v_lines->entered_line);
	free(g_v_lines->expanded_line);
	free(g_v_lines->trimmed_line);
	free(g_v_lines->dollar_processed);
	return (1);
}

int	null_lines(t_line_processing_history *g_v_lines)
{
	g_v_lines->got_command_yet = 0;
	g_v_lines->entered_line = 0;
	g_v_lines->expanded_line = 0;
	g_v_lines->trimmed_line = 0;
	g_v_lines->dollar_processed = 0;
	g_v_lines->is_next_a_command = 0;
	g_v_lines->command_table = 0;
	g_v_lines->iterator = 0;
	g_v_lines->process_id = 0;
	g_v_lines->commands_number = 0;
	return (1);
}

void	duplicate_envirement_vars(t_line_processing_history *g_v_lines,
	char **env)
{
	int		env_vars_count;
	char	**array;
	int		i;

	i = 0;
	env_vars_count = 0;
	while (env[env_vars_count])
		env_vars_count++;
	g_v_lines->env_vars = malloc(sizeof(char *) * (env_vars_count + 1));
	array = g_v_lines->env_vars;
	while (i < env_vars_count)
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	array[i] = 0;
}

int	initialize_v_lines(t_line_processing_history *g_v_lines, char **env)
{
	g_v_lines->exit_status = 0;
	g_v_lines->command_table = 0;
	g_v_lines->is_next_a_command = 0;
	g_v_lines->iterator = 0;
	g_v_lines->process_id = 0;
	g_v_lines->parent_id = 11;
	g_v_lines->got_command_yet = 0;
	g_v_lines->entered_line = 0;
	g_v_lines->expanded_line = 0;
	g_v_lines->trimmed_line = 0;
	g_v_lines->dollar_processed = 0;
	duplicate_envirement_vars(g_v_lines, env);
	return (1);
}

void	free_env(char **arr)
{
	int	i;
	int	env_vars_count;

	env_vars_count = 0;
	i = 0;
	while (arr[env_vars_count])
		env_vars_count++;
	while (i < env_vars_count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	handle_exit(void)
{
	printf("exit\n");
	free_env(g_v_lines->env_vars);
	free_all(g_v_lines);
	tcsetattr(0, TCSANOW, &g_v_lines->terminal_settings);
	system("leaks minishell");
	exit(g_v_lines->exit_status);
}

int	fill_is_a_command(t_line_processing_history *g_v_lines,
	int redirection_number)
{
	if (redirection_number == 1)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 2)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 3)
		g_v_lines->is_next_a_command = 1;
	else if (redirection_number == 4)
		g_v_lines->is_next_a_command = 2;
	return (1);
}

int	fill_command_type(t_commandtable *command_table, int type)
{
	if (type == 0 || type == 10)
	{
		command_table->is_a_command = 1;
		g_v_lines->got_command_yet = 1;
	}
	else if (type == 1)
		command_table->is_a_file = 1;
	else if (type == 3)
		command_table->is_a_file_r = 1;
	else if (type == 4)
		command_table->is_heredoc = 1;
	else if (type == 2)
		command_table->is_a_file_a = 1;
	return (1);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse)
{
	char	c;

	c = '\n';
	signum += 0;
	write(1, &c, 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	in_herdoc(int signum)
{
	char	c;

	c = '\n';
	write(1, &c, 1);
}

void	ctrl_backslash_handler(int signum)
{
	signum += 0;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	get_parent_id(int signum, siginfo_t *siginfo, void *noUse)
{
	g_v_lines->parent_id = siginfo->si_pid;
}

int	handle_signals(void)
{
	g_v_lines->sa.sa_sigaction = &ctrl_c_handler;
	g_v_lines->sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &g_v_lines->sa, 0);
	signal(SIGQUIT, &ctrl_backslash_handler);
	return (1);
}

void	null_command_table_arguments(t_commandtable *command_table)
{
	command_table->argument = 0;
	command_table->command = 0;
	command_table->is_a_file_a = 0;
	command_table->is_a_file_r = 0;
	command_table->limiter = 0;
	command_table->is_a_command = 0;
	command_table->is_a_file = 0;
	command_table->is_heredoc = 0;
	command_table->limiter = 0;
	command_table->pipe = 0;
	command_table->redirections = 0;
	command_table->input_fd = 0;
	command_table->output_fd = 1;
	command_table->self_input_fd = -1;
	command_table->self_output_fd = -1;
}

void	free_arguments(t_arguments *argument)
{
	t_arguments	*arg;

	while (argument)
	{
		arg = argument->next;
		if (argument->arg)
		{
			free(argument->arg);
			argument->arg = 0;
		}
		free(argument);
		argument = arg;
	}
}

void	free_command_table_content(t_commandtable *command_table)
{
	if (command_table->command)
		free(command_table->command);
	if (command_table->argument)
		free_arguments(command_table->argument);
	if (command_table->limiter)
		free(command_table->limiter);
	null_command_table_arguments(command_table);
}

void	free_command_table(t_commandtable *command_table)
{
	t_commandtable	*table;

	while (command_table)
	{
		table = command_table->next;
		free_command_table_content(command_table);
		free(command_table);
		command_table = table;
	}
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

void	initialize_command_infos(t_commandtable *command_table)
{
	null_command_table_arguments(command_table);
	command_table->command = 0;
	command_table->argument = 0;
	command_table->is_a_command = 0;
	command_table->is_a_file = 0;
	command_table->is_heredoc = 0;
	command_table->is_a_file_a = 0;
	command_table->is_a_file_r = 0;
	command_table->limiter = 0;
	command_table->pipe = 0;
	command_table->redirections = 0;
	command_table->next = 0;
}

t_commandtable	*get_last_command_line(t_commandtable *command_table)
{
	while (command_table->next != 0)
		command_table = command_table->next;
	return (command_table);
}

int	initialize_command_table_node(t_line_processing_history *g_v_lines)
{
	t_commandtable	*command_table;
	t_commandtable	*temp;

	if (!g_v_lines->command_table)
	{
		g_v_lines->command_table = malloc(sizeof(t_commandtable));
		command_table = g_v_lines->command_table;
		command_table->previous = 0;
		initialize_command_infos(command_table);
	}
	else
	{
		temp = get_last_command_line(g_v_lines->command_table);
		command_table = malloc(sizeof(t_commandtable));
		temp->next = command_table;
		command_table->previous = temp;
		initialize_command_infos(command_table);
	}
	return (1);
}

int	whitespaces(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
		|| c == '\r' || c == '\v' || c == '\f');
}

void	free_all(t_line_processing_history *g_v_lines)
{
	free_command_table(g_v_lines->command_table);
	free_lines(g_v_lines);
	null_lines(g_v_lines);
}

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
	else if (permission == 0)
		r_fd = make_herdoc_pipe(file_name);
	if (r_fd == -1 || w_fd == -1)
	{
		g_v_lines->exit_status = 1;
		printf("No such file or directory \n");
		return (0);
	}
	else if (r_fd == -2)
		return (0);
	file_opener_condition(r_fd, w_fd, read_fd, write_fd);
	return (1);
}

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

t_commandtable	*late_command(int pipe, int redirection)
{
	t_commandtable	*command_table;

	initialize_command_table_node(g_v_lines);
	command_table = get_last_command_line(g_v_lines->command_table);
	command_table->pipe = pipe;
	command_table->redirections = redirection;
	command_table->is_a_command = 1;
	return (command_table);
}

int	token_stop(char *line, int i)
{
	while (whitespaces(line[i]))
		i++;
	if (line[i] == 34 || line[i] == 39)
		return (0);
	else
		return (1);
}

t_commandtable	*fill_arg_c(t_commandtable *late_table,
		t_commandtable *command_table, char *token)
{
	late_table = late_command(command_table->pipe, command_table->redirections);
	late_table->command = token;
	command_table->pipe = 0;
	command_table->redirections = 0;
	g_v_lines->got_command_yet = 1;
	return (late_table);
}

void	fill_arguments(t_commandtable *command_table, char *line, int *index)
{
	int				i;
	int				j;
	char			*token;
	t_arguments		*current_argument;
	t_commandtable	*late_table;

	i = *index;
	while (1)
	{
		j = token_stop(line, i);
		token = clean_token(line, &i);
		if (token[0] == 0 && j)
		{
			free(token);
			break ;
		}
		if (g_v_lines->got_command_yet == 0)
		{
			late_table = fill_arg_c(late_table, command_table, token);
			continue ;
		}
		initialize_argument_node(command_table);
		current_argument = get_last_argument(command_table->argument);
		current_argument->arg = token;
	}
}

void	fill_command(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void	fill_file(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void	fill_limiter(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	command_table->limiter = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void	initialize_argument_node(t_commandtable *command_table)
{
	t_arguments	*argument;
	t_arguments	*temp;

	if (!command_table->argument)
	{
		command_table->argument = malloc(sizeof(t_arguments));
		argument = command_table->argument;
		argument->previous = 0;
		argument->arg = 0;
		argument->next = 0;
	}
	else
	{
		temp = get_last_argument(command_table->argument);
		argument = malloc(sizeof(t_arguments));
		temp->next = argument;
		argument->previous = temp;
		argument->arg = 0;
		argument->next = 0;
	}
}

t_arguments	*get_last_argument(t_arguments *argument)
{
	if (argument)
		while (argument->next != 0)
			argument = argument->next;
	return (argument);
}

int	split_into_table(char *line, t_commandtable *command_table)
{
	int	i;

	i = 0;
	if (command_table->is_a_command)
		fill_command(line, command_table);
	else if (command_table->is_a_file || command_table->is_a_file_a
		|| command_table->is_a_file_r)
		fill_file(line, command_table);
	else if (command_table->is_heredoc)
		fill_limiter(line, command_table);
	return (1);
}

void	unclosed_quotes(void)
{
	g_v_lines->exit_status = 1;
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
		i++;
	}
	*end_quote = i;
	return (line);
}

char	*process_single_quotes(char *line, int *end_quote,
	t_line_processing_history *g_v_lines)
{
	int	i;

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

int	check_pipe_error(char *line, int i)
{
	while (whitespaces(line[i]) && line[i])
		i++;
	if (line[i])
		return (0);
	else
		return (1);
}

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

char	*get_var(char *var)
{
	char	*var_value;

	var_value = getenv(var);
	free(var);
	return (var_value);
}

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

char	*dollar_check_compliment_0(char *line)
{
	free(line);
	g_v_lines->exit_status = 1;
	printf("Insert process ID of current bash instance here,\
but Im not supposed to handle it :D\n");
	return (0);
}

void	dollar_check_compliment_1(char *line, int i, int len)
{
	if (g_v_lines->dollar_processed)
		free(g_v_lines->dollar_processed);
	g_v_lines->dollar_processed = expand_dollar(line, i + 1, len, 0);
}

char	*dollar_check_compliment_2(char *line, int j)
{
	g_v_lines->dollar_processed = expand_dollar(line, j, 1, 1);
	return (ft_strdup(g_v_lines->dollar_processed));
}

void	dollar_check_compliment_3(char *line, int j, int *len)
{
	if (line[j] <= 48 || line[j] >= 57)
		while (ft_isalnum(line[j++]))
			*len = *len + 1;
}

char	*dollar_check(int *index,
		t_line_processing_history *g_v_lines, char *line)
{
	t_iters1	iters;

	iters.len = 0;
	iters.i = *index;
	if (line[iters.i] == '$')
	{
		iters.j = iters.i + 1;
		if (ft_isalnum(line[iters.j]) || line[iters.j] == '$')
		{
			if (line[iters.j] == '$')
				return (dollar_check_compliment_0(line));
			else
			{
				dollar_check_compliment_3(line, iters.j, &(iters.len));
				dollar_check_compliment_1(line, iters.i, iters.len);
				if (!g_v_lines->dollar_processed)
					return (0);
				line = ft_strdup(g_v_lines->dollar_processed);
			}
		}
		else if (line[iters.j] == '?')
			line = dollar_check_compliment_2(line, iters.j);
	}
	*index = iters.i;
	return (line);
}

char	*number_to_redirection(int c)
{
	if (c == 1)
		return (ft_strdup(">"));
	else if (c == 2)
		return (ft_strdup(">>"));
	else if (c == 3)
		return (ft_strdup("<"));
	else if (c == 4)
		return (ft_strdup("<<"));
	else if (c == 10)
		return (ft_strdup("|"));
	else
		return (0);
}

int	reached_a_redirection_or_end(char c)
{
	if (c == '|')
		return (10);
	if (c == '>')
		return (1);
	if (c == '<')
		return (3);
	if (c == '\0')
		return (69);
	return (0);
}

int	pipe_redirection(char c, char after_c)
{
	if (c == '|')
		return (10);
	else if (c == '>')
	{
		if (after_c == '>')
			return (2);
		else
			return (1);
	}
	else if (c == '<')
	{
		if (after_c == '<')
			return (4);
		else
			return (3);
	}
	return (0);
}

int	check_previous_redirection(char *line, int start)
{
	int	prev;

	if (start >= 2)
	{
		prev = reached_a_redirection_or_end(line[start - 1]);
		if (reached_a_redirection_or_end(line[start - 2]) == prev)
			return (prev + 1);
		else
			return (prev);
	}
	else if (start == 1)
	{
		return (reached_a_redirection_or_end(line[start - 1]));
	}
	else
		return (0);
}

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

int	is_full_of_whitespaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!whitespaces(line[i]))
			return (0);
		i++;
	}
	return (1);
}

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

int	find_duplicate_redirections_compliment_0(char *line)
{
	free(line);
	g_v_lines->exit_status = 1;
	printf("multiple redirections\n");
	return (1);
}

int	find_duplicate_redirections_compliment_1(t_iters3 iters, int i)
{
	if (iters.redirection == 2 || iters.redirection == 4)
			i++;
	return (i);
}

int	find_duplicate_redirections(char *line, int i)
{
	t_iters3	iters;

	iters.j = 0;
	while (line[i] && line[i] != 34 && line[i] != 39)
	{
		iters.redirection = pipe_redirection(line[i], line[i + 1]);
		i = find_duplicate_redirections_compliment_1(iters, i);
		if (iters.redirection)
		{
			iters.j = i + 1;
			while (whitespaces(line[iters.j]))
				iters.j++;
			iters.previous_redirection = reached_a_redirection_or_end
				(line[iters.j]);
			if (iters.redirection == 10)
			{
				if (iters.previous_redirection == 10)
					return (find_duplicate_redirections_compliment_0(line));
			}
			else if (iters.previous_redirection && line[iters.j] != 0)
				return (find_duplicate_redirections_compliment_0(line));
		}
		i++;
	}
	return (0);
}

int	herdoc_error(char *line, int i)
{
	i = i + 2;
	while (whitespaces(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		g_v_lines->exit_status = 1;
		printf("Parse error, nothing or newline after redirection\n");
		return (1);
	}
	return (0);
}

void	delete_arg_node(t_commandtable *command_table,
			t_arguments *arg_to_delete)
{
	t_arguments	*previous;
	t_arguments	*next;

	next = arg_to_delete->next;
	previous = arg_to_delete->previous;
	if (arg_to_delete->arg)
		free(arg_to_delete->arg);
	free(arg_to_delete);
	if (previous)
		previous->next = next;
	else
		command_table->argument = next;
	if (next)
		next->previous = previous;
}

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == -1)
			return (1);
		i++;
	}
	return (0);
}

void	change_back_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = '*';
		i++;
	}
}

int	handle_command_wildcard(t_commandtable *command_table)
{
	t_arguments	*matched_args;
	t_arguments	*next;
	int			i;

	i = 0;
	matched_args = match_with_directory(command_table->command);
	if (!matched_args)
	{
		change_back_wildcard(command_table->command);
		return (0);
	}
	command_table->command = matched_args->arg;
	matched_args = matched_args->next;
	if (matched_args)
	{
		matched_args->previous = 0;
		next = command_table->argument;
		command_table->argument = matched_args;
		matched_args = get_last_argument(matched_args);
		matched_args->next = next;
	}
	return (1);
}

t_arguments	*handle_args_wildcard(t_commandtable *command_table,
			t_arguments *args)
{
	t_arguments	*next;
	t_arguments	*previous;
	t_arguments	*matched_args;

	matched_args = match_with_directory(args->arg);
	if (!matched_args)
	{
		change_back_wildcard(args->arg);
		return (args);
	}
	next = args->next;
	previous = args->previous;
	delete_arg_node(command_table, args);
	if (previous)
		previous->next = matched_args;
	else
		command_table->argument = matched_args;
	matched_args->previous = previous;
	matched_args = get_last_argument(matched_args);
	matched_args->next = next;
	return (next);
}

int	process_wildcards(t_commandtable *command_table)
{
	t_arguments	*args;

	while (command_table)
	{
		if (command_table->command)
			if (check_wildcard(command_table->command))
				handle_command_wildcard(command_table);
		args = command_table->argument;
		while (args)
		{
			if (check_wildcard(args->arg))
			{
				args = handle_args_wildcard(command_table, args);
				continue ;
			}
			args = args->next;
		}
		command_table = command_table->next;
	}
	return (1);
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

void	e_l_2_c_d_compliment(t_iters5 iters, char *line, int redirection_number)
{
	if (iters.len && !is_full_of_whitespaces(line))
	{
		initialize_command_table_node(g_v_lines);
		iters.command_table = get_last_command_line(g_v_lines->command_table);
		fill_command_type(iters.command_table, iters.previous_redirection);
		g_v_lines->is_next_a_command = 0;
		if (redirection_number == 10)
			iters.command_table->pipe = 1;
		else if (redirection_number)
		{
			iters.command_table->redirections = redirection_number;
			fill_is_a_command(g_v_lines, redirection_number);
		}
		split_into_table(line, iters.command_table);
	}
	else
		fill_is_a_command(g_v_lines, redirection_number);
}

int	expanded_line_2_command_table(t_line_processing_history *g_v_lines,
		int start, int redirection_number, char *line)
{
	t_iters5	iters;

	iters.start_iter = start;
	iters.len = 0;
	iters.previous_redirection = check_previous_redirection(line, start);
	while (!reached_a_redirection_or_end(line[iters.start_iter]))
	{
		iters.start_iter++;
		iters.len++;
	}
	iters.temp = line;
	line = ft_substr(line, start, iters.len);
	free(iters.temp);
	e_l_2_c_d_compliment(iters, line, redirection_number);
	free(line);
	return (1);
}

int	parse(t_line_processing_history *g_v_lines)
{
	if (!expandline(g_v_lines))
		return (0);
	return (1);
}

void print_ct(t_line_processing_history *g_v_lines)
{
	t_commandtable *c_table;
	t_arguments *argi;
	c_table = g_v_lines->command_table;
	fflush(stdout);
	while (c_table)
	{
		printf("is command : %d, is a file_toWrite %d, is_herdoc %d, is append %d,file_toRead%d\n", c_table->is_a_command, c_table->is_a_file, c_table->is_heredoc, c_table->is_a_file_a, c_table->is_a_file_r);
		printf("command: {%s}\n", c_table->command);
		printf("limiter: {%s}\n", c_table->limiter);
		printf("is next pipe:%d, is next redirection:%d\n", c_table->pipe, c_table->redirections);
		printf("input_fd : %d,output_fd : %d\n", c_table->input_fd, c_table->output_fd);
		printf("arguements: \n");
		argi = c_table->argument;
		while (argi != 0)
		{
			printf(" arg : {%s}\n", argi->arg);
			argi = argi->next;
		}
		printf(" \n\n\n\n");
		c_table = c_table->next;
	}
	fflush(stdout);
}

void	delete_table_node(t_commandtable *command_table)
{
	t_commandtable	*previous_temp;
	t_commandtable	*next_temp;

	previous_temp = command_table->previous;
	next_temp = command_table->next;
	if (command_table->command)
		free(command_table->command);
	if (command_table->limiter)
		free(command_table->limiter);
	free(command_table);
	if (previous_temp)
		previous_temp->next = next_temp;
	else
		g_v_lines->command_table = next_temp;
	if (next_temp)
		next_temp->previous = previous_temp;
}

int	clean_nodes(t_commandtable *command_table)
{
	t_commandtable	*temp;

	while (command_table)
	{
		temp = command_table->next;
		if (command_table->is_a_command == 0)
			delete_table_node(command_table);
		command_table = temp;
	}
	return (1);
}

void	link_argument_nodes(t_commandtable *node_to_fill,
		t_commandtable *current_node)
{
	t_arguments	*last_element;
	t_arguments	*child_args_head;
	t_arguments	*parent_args_head;

	parent_args_head = node_to_fill->argument;
	child_args_head = current_node->argument;
	current_node->argument = 0;
	last_element = get_last_argument(parent_args_head);
	if (!last_element)
		node_to_fill->argument = child_args_head;
	else
		last_element->next = child_args_head;
	if (child_args_head)
		child_args_head->previous = last_element;
}

t_commandtable	*get_table_after_pipe(t_commandtable *current_node)
{
	t_commandtable	*command_table;

	command_table = current_node;
	while (command_table->previous)
	{
		if (command_table->previous->pipe == 1)
			break ;
		command_table = command_table->previous;
	}
	return (command_table);
}

void	close_fds(t_commandtable *command_table)
{
	while (command_table)
	{
		if (command_table->input_fd != 0)
			close(command_table->input_fd);
		if (command_table->output_fd != 1)
			close(command_table->output_fd);
		command_table = command_table->next;
	}
}

t_commandtable	*find_duplicate_files(t_commandtable *command_table)
{
	t_commandtable	*duplicate;
	char			*file_name;

	duplicate = 0;
	file_name = command_table->command;
	command_table = command_table->next;
	while (command_table)
	{
		if (command_table->is_a_file_a == 1 || command_table->is_a_file == 1)
		{
			if (command_table->previous)
			{
				if (command_table->previous->pipe == 1)
					break ;
			}
			if (!ft_strncmp(command_table->command, file_name, max
					(ft_strlen(file_name), ft_strlen(command_table->command))))
			{
				duplicate = command_table;
			}
		}
		command_table = command_table->next;
	}
	return (duplicate);
}

void	handle_priority(t_commandtable *file1, t_commandtable *file2)
{
	int	overwrite;

	overwrite = 0;
	if (file1->is_a_file || file2->is_a_file)
		overwrite = 1;
	if (overwrite)
	{
		file1->is_a_file_a = 0;
		file2->is_a_file_a = 0;
		file1->is_a_file = 1;
		file2->is_a_file = 1;
	}
}

void	duplicate_files(t_commandtable *command_table)
{
	t_commandtable	*duplicate;

	while (command_table)
	{
		if (command_table->is_a_file_a == 1 || command_table->is_a_file == 1)
		{
			duplicate = find_duplicate_files(command_table);
			if (duplicate)
				handle_priority(command_table, duplicate);
		}
		command_table = command_table->next;
	}
}

int	open_all(t_commandtable *command_table)
{
	t_commandtable	*head_node;
	int				open_return;

	head_node = command_table;
	while (command_table)
	{
		if (command_table->is_a_file)
			open_return = file_opener(3, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_a_file_a)
			open_return = file_opener(2, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_a_file_r)
			open_return = file_opener(1, command_table->command,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		else if (command_table->is_heredoc)
			open_return = file_opener(0, command_table->limiter,
					&command_table->self_input_fd,
					&command_table->self_output_fd);
		command_table = command_table->next;
	}
	return (open_return);
}

void	get_node_to_fill_compliment(t_commandtable *node_to_fill)
{
	if (node_to_fill->is_a_command == 0)
	{
		node_to_fill->is_a_command = 2;
		free(node_to_fill->command);
		node_to_fill->command = 0;
		if (node_to_fill->self_input_fd != -1)
			close(node_to_fill->self_input_fd);
		if (node_to_fill->self_output_fd != -1)
			close(node_to_fill->self_output_fd);
	}
}

t_commandtable	*get_node_to_fill(t_commandtable *current_node)
{
	t_commandtable	*node_to_fill;

	current_node = get_table_after_pipe(current_node);
	node_to_fill = current_node;
	while (current_node && current_node->pipe == 0)
	{
		if (current_node->is_a_command == 1)
		{
			node_to_fill = current_node;
			break ;
		}
		if (current_node->next)
			current_node = current_node->next;
		else
			break ;
	}
	if (current_node->is_a_command)
		node_to_fill = current_node;
	get_node_to_fill_compliment(node_to_fill);
	return (node_to_fill);
}

void	transfer_node_infos(t_commandtable *node_to_fill,
			t_commandtable *current_node)
{
	if (current_node->self_input_fd != -1)
	{
		if (node_to_fill->input_fd != 0)
			close(node_to_fill->input_fd);
		node_to_fill->input_fd = current_node->self_input_fd;
	}
	if (current_node->self_output_fd != -1)
	{
		if (node_to_fill->output_fd != 1)
			close(node_to_fill->output_fd);
		node_to_fill->output_fd = current_node->self_output_fd;
	}
	link_argument_nodes(node_to_fill, current_node);
}

int	built_in_check(char *line)
{
	if (!ft_strncmp("cd", to_lower(line), max(ft_strlen(line), ft_strlen(""))))
		return (11);
	else if (!ft_strncmp("export", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (13);
	else if (!ft_strncmp("unset", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (14);
	else if (!ft_strncmp("exit", to_lower(line),
			max(ft_strlen(line), ft_strlen(""))))
		return (15);
	else
		return (0);
}

int	is_built_in(t_line_processing_history *g_v_lines)
{
	t_commandtable	*command_table;
	t_commandtable	*command;
	int				i;
	int				is_built_in;

	is_built_in = 0;
	i = 0;
	command_table = g_v_lines->command_table;
	while (command_table)
	{
		if (command_table->is_a_command == 1)
		{
			command = command_table;
			i++;
		}
		command_table = command_table->next;
	}
	if (i == 1)
		is_built_in = built_in_check(command->command);
	return (is_built_in);
}

void	execute_built_in(int built_in_number)
{
	printf("execute built_in\n");
}

int	process_command_table_compliment_0(t_commandtable *current_node,
		t_commandtable *node_to_fill, int built_in_number)
{
	while (current_node)
	{
		node_to_fill = get_node_to_fill(current_node);
		if (current_node != node_to_fill)
		{
			transfer_node_infos(node_to_fill, current_node);
		}
		current_node = current_node->next;
	}
	if (built_in_number)
		execute_built_in(built_in_number);
	return (0);
}

int	process_command_table(t_line_processing_history *g_v_lines)
{
	t_commandtable	*node_to_fill;
	t_commandtable	*current_node;
	int				built_in_number;

	current_node = g_v_lines->command_table;
	duplicate_files(current_node);
	built_in_number = is_built_in(g_v_lines);
	signal(SIGINT, &in_herdoc);
	g_v_lines->parent_id = fork();
	if (g_v_lines->parent_id != 0)
		return (process_command_table_compliment_0(current_node, \
			node_to_fill, built_in_number));
	signal(SIGINT, SIG_DFL);
	if (open_all(current_node) == 0)
		return (0);
	while (current_node)
	{
		node_to_fill = get_node_to_fill(current_node);
		if (current_node != node_to_fill)
			transfer_node_infos(node_to_fill, current_node);
		current_node = current_node->next;
	}
	clean_nodes(g_v_lines->command_table);
	process_wildcards(g_v_lines->command_table);
	return (1);
}

int	processline(t_line_processing_history *g_v_lines)
{
	int	parse_success;

	g_v_lines->trimmed_line = ft_strtrim(g_v_lines->entered_line, " 		");
	if (!ft_strncmp(g_v_lines->trimmed_line, "exit", \
			max(ft_strlen(g_v_lines->trimmed_line), 4)))
	{
		handle_exit();
	}
	parse_success = parse(g_v_lines);
	if (parse_success)
		parse_success = process_command_table(g_v_lines);
	if (parse_success)
	{
		print_ct(g_v_lines);
		// syntax_check();
		// execute(g_v_lines);//talk bout if theres smth that needs to go back here in the parsin
	}
	return (1);
}

int	readline_loop(t_line_processing_history *g_v_lines)
{
	while (1)
	{
		handle_signals();
		g_v_lines->entered_line = readline("bash tsetta -0.1 $ ");
		if (!g_v_lines->entered_line)
			handle_exit();
		if (!is_full_of_whitespaces(g_v_lines->entered_line))
		{
			add_history(g_v_lines->entered_line);
			processline(g_v_lines);
		}
		if (g_v_lines->parent_id != 0)
			wait(NULL);
		else
		{
			close_fds(g_v_lines->command_table);
			free_all(g_v_lines);
			free_env(g_v_lines->env_vars);
			return (1);
		}
		free_all(g_v_lines);
	}
}

int	main(int argc, char **argv, char **env)
{
	struct termios	oldtio;
	struct termios	newtio;

	g_v_lines = malloc(sizeof(t_line_processing_history));
	initialize_v_lines(g_v_lines, env);
	handle_signals();
	tcgetattr(0, &oldtio);
	g_v_lines->terminal_settings = oldtio;
	oldtio.c_lflag &= ~ICANON;
	oldtio.c_lflag &= ECHO;
	tcsetattr(0, TCSANOW, &oldtio);
	return (readline_loop(g_v_lines));
	return (1);
}
