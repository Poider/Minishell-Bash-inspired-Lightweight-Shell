/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:10 by mel-amma          #+#    #+#             */
/*   Updated: 2022/03/04 14:30:29 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line_processing_history *v_lines;

int free_lines(t_line_processing_history *v_lines)
{
	free(v_lines->entered_line);
	free(v_lines->expanded_line);
	free(v_lines->trimmed_line);
	free(v_lines->dollar_processed);
	return 1;
}

int null_lines(t_line_processing_history *v_lines)
{
	v_lines->got_command_yet = 0;
	v_lines->entered_line = 0;
	v_lines->expanded_line = 0;
	v_lines->trimmed_line = 0;
	v_lines->dollar_processed = 0;
	v_lines->is_next_a_command = 0;
	v_lines->command_table = 0;

	return (1);
}

void duplicate_envirement_vars(t_line_processing_history *v_lines, char **env)
{
	int env_vars_count;
	char **array;
	int i;

	i = 0;
	env_vars_count = 0;
	while (env[env_vars_count])
		env_vars_count++;

	v_lines->env_vars = malloc(sizeof(char *) * (env_vars_count + 1));
	array = v_lines->env_vars;
	while (i < env_vars_count)
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	array[i] = 0;
}

int initialize_v_lines(t_line_processing_history *v_lines, char **env)
{

	v_lines->exit_status = 0;
	v_lines->command_table = 0;
	v_lines->is_next_a_command = 0;
	v_lines->process_id = 11112;
	v_lines->parent_id = 11;
	v_lines->got_command_yet = 0;
	v_lines->entered_line = 0;
	v_lines->expanded_line = 0;
	v_lines->trimmed_line = 0;
	v_lines->dollar_processed = 0;
	duplicate_envirement_vars(v_lines, env);
	return 1;
}

void free_env(char **arr)
{
	int i;
	int env_vars_count;

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

int handle_exit()
{
	printf("exit\n");
	free_env(v_lines->env_vars);
	free_all(v_lines);
	tcsetattr(0, TCSANOW, &v_lines->terminal_settings);
	system("leaks minishell");
	exit(v_lines->exit_status);
}

int fill_is_a_command(t_line_processing_history *v_lines, int redirection_number)
{
	if (redirection_number == 1)
		v_lines->is_next_a_command = 1;
	else if (redirection_number == 2)
		v_lines->is_next_a_command = 1;
	else if (redirection_number == 3)
		v_lines->is_next_a_command = 1;
	else if (redirection_number == 4)
		v_lines->is_next_a_command = 2;

	return 1;
}

int fill_command_type(t_commandtable *command_table, int type)
{
	if (type == 0 || type == 10)
	{
		command_table->is_a_command = 1;
		v_lines->got_command_yet = 1;
	}
	else if (type == 1)
		command_table->is_a_file = 1;
	else if (type == 3)
		command_table->is_a_fileR = 1;
	else if (type == 4)
		command_table->is_heredoc = 1;
	else if (type == 2)
		command_table->is_a_fileA = 1;
	return 1;
}

int max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse)
{
	char c = '\n';

	signum += 0;
	write(1, &c, 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void in_herdoc(int signum)
{
	char c = '\n';
	write(1, &c, 1);
}

void ctrl_backslash_handler(int signum)
{
	signum += 0;

	rl_on_new_line();
	rl_redisplay();
	return;
}

void get_parent_id(int signum, siginfo_t *siginfo, void *noUse)
{
	if (v_lines->process_id == 0)
	{
		v_lines->parent_id = siginfo->si_pid;
	}
}

void exiting(int signum)
{
	if (v_lines->process_id != 0)
	{
		exit(0);
	}
}

int handle_signals()
{
	v_lines->sa.sa_sigaction = &ctrl_c_handler;
	v_lines->sa.sa_flags = SA_SIGINFO;
	// v_lines->sa.sa_sigaction = &get_parent_id;
	// v_lines->sa.sa_flags = SA_SIGINFO;
	// signal(SIGINT, &ctrl_c_handler);
	sigaction(SIGINT, &v_lines->sa, 0);
	signal(SIGQUIT, &ctrl_backslash_handler);
	// sigaction(SIGUSR1, &v_lines->sa, 0);
	// signal(SIGUSR2, &exiting);

	return (1);
}

void null_command_table_arguments(t_commandtable *command_table)
{
	command_table->argument = 0;
	command_table->command = 0;
	command_table->is_a_fileA = 0;
	command_table->is_a_fileR = 0;
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

void free_arguments(t_arguments *argument)
{
	t_arguments *arg;

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

void free_command_table_content(t_commandtable *command_table)
{
	if (command_table->command)
		free(command_table->command);
	if (command_table->argument)
		free_arguments(command_table->argument);
	if (command_table->limiter)
		free(command_table->limiter);
	null_command_table_arguments(command_table);
}

void free_command_table(t_commandtable *command_table)
{
	t_commandtable *table;

	while (command_table)
	{
		table = command_table->next;
		free_command_table_content(command_table);
		free(command_table);
		command_table = table;
	}
}

char *pipe_error(char *line, int i)
{
	char *side_2;
	char *temp;

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
	return line;
}

char *redirection_error(char *line, int i)
{
	char *side_2;
	char *temp;

	side_2 = NULL;
	if (check_pipe_error(line, i + 1))
	{
		v_lines->exit_status = 1;
		free(line);
		printf("Parse error, nothing or newline after redirection\n");
		return (0);
	}
	return line;
}

char *check_redirection_error(char *line, int i, int redirection)
{
	if (redirection == 10)
		line = pipe_error(line, i);
	else if (redirection >= 1 && redirection <= 4)
		line = redirection_error(line, i);

	return (line);
}

void initialize_command_infos(t_commandtable *command_table)
{
	null_command_table_arguments(command_table);
	command_table->command = 0;
	command_table->argument = 0;
	command_table->is_a_command = 0;
	command_table->is_a_file = 0;
	command_table->is_heredoc = 0;
	command_table->is_a_fileA = 0;
	command_table->is_a_fileR = 0;
	command_table->limiter = 0;
	command_table->pipe = 0;
	command_table->redirections = 0;
	command_table->next = 0;
}

t_commandtable *get_last_command_line(t_commandtable *command_table)
{
	while (command_table->next != 0)
		command_table = command_table->next;
	return (command_table);
}

int initialize_command_table_node(t_line_processing_history *v_lines)
{

	t_commandtable *command_table;
	t_commandtable *temp;

	if (!v_lines->command_table)
	{
		v_lines->command_table = malloc(sizeof(t_commandtable));
		command_table = v_lines->command_table;
		command_table->previous = 0;
		initialize_command_infos(command_table);
	}
	else
	{
		temp = get_last_command_line(v_lines->command_table);
		command_table = malloc(sizeof(t_commandtable));
		temp->next = command_table;
		command_table->previous = temp;
		initialize_command_infos(command_table);
	}

	return (1);
}

int whitespaces(char c)
{
	return (c == '\n' || c == '\t' || c == ' ' || c == '\r' || c == '\v' || c == '\f');
}

void free_all(t_line_processing_history *v_lines)
{
	free_command_table(v_lines->command_table);
	free_lines(v_lines);
	null_lines(v_lines);
}

int make_herdoc_pipe(char *limiter)
{
	int fd[2];
	char *line;
	char newliney = '\n';
	pipe(fd);
	line = "$^(!)g1?e4t_2i3n";

	while (1)
	{
		line = readline("heredoc>> ");
		if (!line)
		{
			close(fd[0]);
			close(fd[1]);

			return -2;
		}
		if (!ft_strncmp(line, limiter, max(ft_strlen(limiter), ft_strlen(line))))
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], &newliney, 1);
		if (line)
			free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int file_opener(int permission, char *file_name, int *read_fd, int *write_fd)
{
	int r_fd;
	int w_fd;

	r_fd = 0;
	w_fd = 0;

	if (permission == 1)
	{
		r_fd = open(file_name, O_RDONLY);
	}
	else if (permission == 2)
		w_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (permission == 3)
		w_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (permission == 0)
		r_fd = make_herdoc_pipe(file_name);

	if (r_fd == -1 || w_fd == -1)
	{
		v_lines->exit_status = 1;
		printf("No such file or directory \n");
		return 0;
	}
	else if (r_fd == -2)
		return 0;
	if (r_fd)
		*read_fd = r_fd;
	if (w_fd)
		*write_fd = w_fd;
	return 1;
}

char *delete_quote(char *token, int *start_quote_position)
{
	int i;
	char *temp;
	char *side_1;
	char *side_2;
	char *middle_stuff;
	char *joined;
	int quote_type;
	i = *start_quote_position;
	quote_type = token[i];
	i++;
	side_1 = ft_substr(token, 0, *start_quote_position);
	while (token[i] != quote_type)
		i++;
	middle_stuff = ft_substr(token, *start_quote_position + 1, i - 1 - *start_quote_position);
	side_2 = ft_substr(token, i + 1, ft_strlen(token));
	temp = ft_strjoin(side_1, middle_stuff);
	token = ft_strjoin(temp, side_2);
	free(side_1);
	free(side_2);
	free(middle_stuff);
	free(temp);
	*start_quote_position = i - 2;
	return (token);
}

char *clean_token(char *line, int *iteration_position)
{
	char *token;
	char *temp;
	int len;
	int i;
	int j;
	token = ft_strdup(line);
	j = 0;

	temp = NULL;
	i = *iteration_position;
	while (whitespaces(token[i]) && token[i])
		i++;
	*iteration_position = i;

	while (!whitespaces(token[i]) && token[i])
	{
		if (token[i] == 34 || token[i] == 39)
		{
			temp = token;
			token = delete_quote(token, &i);
			free(temp);
			j++;
		}

		i++;
		len++;
	}
	temp = token;
	token = ft_substr(token, *iteration_position, i - *iteration_position);
	free(temp);
	*iteration_position = i + 2 * j;
	return token;
}

t_commandtable *late_command(int pipe, int redirection)
{
	t_commandtable *command_table;

	initialize_command_table_node(v_lines);
	command_table = get_last_command_line(v_lines->command_table);
	command_table->pipe = pipe;
	command_table->redirections = redirection;
	command_table->is_a_command = 1;
	return (command_table);
}

int token_stop(char *line, int i)
{
	while (whitespaces(line[i]))
		i++;
	if (line[i] == 34 || line[i] == 39)
		return 0;
	else
		return 1;
}

void fill_arguments(t_commandtable *command_table, char *line, int *index)
{
	int i;
	int j;
	char *token;
	t_arguments *current_argument;
	t_commandtable *late_table;

	token = 0;
	i = *index;
	while (1)
	{
		j = token_stop(line, i);
		token = clean_token(line, &i);

		if (token[0] == 0 && j)
		{
			free(token);
			break;
		}
		if (v_lines->got_command_yet == 0)
		{
			late_table = late_command(command_table->pipe, command_table->redirections);
			late_table->command = token;
			command_table->pipe = 0;
			command_table->redirections = 0;
			v_lines->got_command_yet = 1;
			continue;
		}
		initialize_argument_node(command_table);
		current_argument = get_last_argument(command_table->argument);
		current_argument->arg = token;
	}
}

void fill_command(char *line, t_commandtable *command_table)
{
	int i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void fill_file(char *line, t_commandtable *command_table)
{
	int i;

	i = 0;
	command_table->command = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void fill_limiter(char *line, t_commandtable *command_table)
{
	int i;

	i = 0;
	command_table->limiter = clean_token(line, &i);
	fill_arguments(command_table, line, &i);
}

void initialize_argument_node(t_commandtable *command_table)
{
	t_arguments *argument;
	t_arguments *temp;

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

t_arguments *get_last_argument(t_arguments *argument)
{
	if (argument)
		while (argument->next != 0)
			argument = argument->next;
	return (argument);
}

int split_into_table(char *line, t_commandtable *command_table)
{
	int i;

	i = 0;
	if (command_table->is_a_command)
		fill_command(line, command_table);
	else if (command_table->is_a_file || command_table->is_a_fileA || command_table->is_a_fileR)
		fill_file(line, command_table);
	else if (command_table->is_heredoc)
		fill_limiter(line, command_table);
	return 1;
}

void unclosed_quotes(void)
{
	v_lines->exit_status = 1;
	printf("You have an unclosed quote\n");
}

char *process_double_quotes(char *line, int *end_quote, t_line_processing_history *v_lines)
{

	int i;

	i = *end_quote + 1;
	while (line[i] != 34)
	{
		if (line[i] == '$')
			line = dollar_check(&i, v_lines, line);
		if (!line)
		{
			return 0;
		}
		if (line[i] == '\0')
		{
			free(line);
			unclosed_quotes();
			return 0;
		}
		i++;
	}
	*end_quote = i;

	return (line);
}

char *process_single_quotes(char *line, int *end_quote, t_line_processing_history *v_lines)
{
	int i;

	i = *end_quote + 1;
	while (line[i] != 39)
	{
		if (line[i] == '\0')
		{
			free(line);
			unclosed_quotes();
			return 0;
		}
		i++;
	}
	*end_quote = i;
	return (line);
}

char *process_quotes(int *index, t_line_processing_history *v_lines, char *line)
{
	int i;

	i = *index;
	if (line[i] == 34)
		line = process_double_quotes(line, &i, v_lines);
	else if (line[i] == 39)
		line = process_single_quotes(line, &i, v_lines);
	*index = i;
	return (line);
}

int check_pipe_error(char *line, int i)
{
	while (whitespaces(line[i]) && line[i])
		i++;
	if (line[i])
		return 0;
	else
		return 1;
}

char *delete_spaces(char *line, int start_eliminating)
{
	char *cleared_line;
	char *side_1;
	char *side_2;
	int i;

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

char *get_var(char *var)
{
	char *var_value;

	var_value = getenv(var);
	free(var);
	return (var_value);
}

int check_file_expansion_named(char *line, int i)
{
	if (i > 0)
	{
		while (whitespaces(line[i]))
			i--;
		if (i > 0)
			if (reached_a_redirection_or_end(line[i]))
			{
				free(line);
				v_lines->exit_status = 1;
				printf("ambiguous redirect\n");
				return 1;
			}
	}
	return 0;
}

char *expand_dollar(char *line, int var_start, int var_len, int type)
{
	char *temp_joined;
	char *joined;
	char *side_1;
	char *side_2;
	char *var_value;
	if (var_len == 0)
		var_len = 1;
	side_1 = ft_substr(line, 0, var_start - 1);
	side_2 = ft_substr(line, var_start + var_len, ft_strlen(line));
	if (type == 0)
		var_value = get_var(ft_substr(line, var_start, var_len));
	else if (type == 1)
		var_value = ft_itoa(v_lines->exit_status);
	temp_joined = ft_strjoin(side_1, var_value);
	joined = ft_strjoin(temp_joined, side_2);
	free(temp_joined);
	free(side_1);
	free(side_2);
	if (type == 0 && ft_strlen(var_value) == 0)
		if (check_file_expansion_named(line, var_start - 2))
			return 0;
	free(line);
	return (joined);
}

char *dollar_check(int *index, t_line_processing_history *v_lines, char *line)
{
	int i;
	int j;
	int len;

	len = 0;
	i = *index;

	if (line[i] == '$')
	{
		j = i + 1;
		if (ft_isalnum(line[j]) || line[j] == '$')
		{
			if (line[j] == '$')
			{
				free(line);
				v_lines->exit_status = 1;
				printf("Insert process ID of current bash instance here, but Im not supposed to handle it :D\n");
				return 0;
			}
			else
			{
				if (line[j] <= 48 || line[j] >= 57)
					while (ft_isalnum(line[j]))
					{
						j++;
						len++;
					}
				if (v_lines->dollar_processed)
					free(v_lines->dollar_processed);
				v_lines->dollar_processed = expand_dollar(line, i + 1, len, 0);
				if (!v_lines->dollar_processed)
					return 0;
				line = ft_strdup(v_lines->dollar_processed);
			}
		}
		else if (line[j] == '?')
		{
			v_lines->dollar_processed = expand_dollar(line, j, 1, 1);
			line = ft_strdup(v_lines->dollar_processed);
		}
	}
	*index = i;

	return (line);
}

char *number_to_redirection(int c)
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
		return 0;
}

int reached_a_redirection_or_end(char c)
{
	if (c == '|')
		return 10;
	if (c == '>')
		return 1;
	if (c == '<')
		return 3;
	if (c == '\0')
		return 69;
	return 0;
}

int pipe_redirection(char c, char after_c)
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

int check_previous_redirection(char *line, int start)
{
	int prev;

	if (start >= 2)
	{
		prev = reached_a_redirection_or_end(line[start - 1]);
		if (reached_a_redirection_or_end(line[start - 2]) == prev)
			return (prev + 1);
		else
			return prev;
	}
	else if (start == 1)
	{
		return (reached_a_redirection_or_end(line[start - 1]));
	}
	else
		return 0;
}

int get_last_pipe(int *flag, char *line)
{
	static int last_start_position;
	int start_position;
	int redirection_number;

	if (*flag == 0)
	{
		last_start_position = 0;
		*flag = 1;
	}
	if (last_start_position == -1)
		return -1;
	start_position = last_start_position;

	if (line[last_start_position])
	{
		redirection_number = pipe_redirection(line[last_start_position], line[last_start_position + 1]);
		while (!redirection_number && line[last_start_position + 1])
		{
			last_start_position++;
			redirection_number = pipe_redirection(line[last_start_position], line[last_start_position + 1]);
		}
		if (line[last_start_position + 1] == '\0')
			last_start_position = -1;
		else
		{
			if (redirection_number == 4)
				last_start_position++;
			last_start_position++;
		}
	}
	return (start_position);
}

int is_full_of_whitespaces(char *line)
{
	int i;

	i = 0;
	if (!line)
		return 1;
	while (line[i])
	{
		if (!whitespaces(line[i]))
			return 0;
		i++;
	}
	return 1;
}

int start_error(char *line)
{
	int i;

	i = 0;
	while (whitespaces(line[i]))
		i++;
	if (line[i] == '|')
	{
		v_lines->exit_status = 1;
		printf("Error: Why u be startin shit with a pipe\n");
		return 1;
	}
	return 0;
}

int find_duplicate_redirections(char *line, int i)
{
	int redirection;
	int j;
	int previous_redirection;

	j = 0;
	while (line[i] && line[i] != 34 && line[i] != 39)
	{

		redirection = pipe_redirection(line[i], line[i + 1]);
		if (redirection == 2 || redirection == 4)
		{
			i++;
		}
		if (redirection)
		{
			j = i + 1;

			while (whitespaces(line[j]))
				j++;
			previous_redirection = reached_a_redirection_or_end(line[j]);

			if (redirection == 10)
			{
				if (previous_redirection == 10)
				{
					free(line);
					v_lines->exit_status = 1;
					printf("multiple redirections\n");
					return 1;
				}
			}
			else if (previous_redirection && line[j] != 0)
			{
				free(line);
				v_lines->exit_status = 1;
				printf("multiple redirections\n");
				return 1;
			}
		}
		i++;
	}
	return 0;
}

int herdoc_error(char *line, int i)
{
	i = i + 2;
	while (whitespaces(line[i]))
		i++;
	if (!line[i])
	{
		free(line);
		v_lines->exit_status = 1;
		printf("Parse error, nothing or newline after redirection\n");
		return 1;
	}

	return 0;
}

void delete_arg_node(t_commandtable *command_table, t_arguments *arg_to_delete)
{
	t_arguments *previous;
	t_arguments *next;
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

int check_wildcard(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if((int)str[i] == -1)
		return 1;
		i++;
	}
	return 0;
}

void change_back_wildcard(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if(str[i] == -1)
			str[i] = '*';
		i++;
	}
}

int handle_command_wildcard(t_commandtable *command_table)
{
	t_arguments *matched_args;
	t_arguments *next;
	int i;

	i = 0;
	matched_args = match_with_directory(command_table->command);
	if(!matched_args)
	{
		change_back_wildcard(command_table->command);
		return 0;
	}
	command_table->command = matched_args->arg;
	matched_args = matched_args ->next;
	if(matched_args)
	{
		matched_args->previous = 0;	
		next = command_table->argument;
		command_table->argument = matched_args;
		matched_args = get_last_argument(matched_args);
		matched_args->next = next;
	}
	
	return 1;

}

t_arguments *handle_args_wildcard(t_commandtable *command_table, t_arguments *args)//should handle the case where arg is the first, if you dont find previous to link it with after deleting the current one then take
													//it and put it as the command table//check the condition of this in link arguments?
{
	t_arguments *next;
	t_arguments *previous;
	t_arguments *matched_args;
	matched_args = match_with_directory(args->arg);
	if(!matched_args)
	{
		change_back_wildcard(args->arg);
		return args;
	}
	next = args->next;
	previous = args->previous;
	
	delete_arg_node(command_table,args);
	if(previous)
		previous->next = matched_args;
	else 
		command_table ->argument = matched_args;
	matched_args->previous = previous;
	matched_args = get_last_argument(matched_args);
	matched_args->next = next;

	return next;
}

int process_wildcards(t_commandtable *command_table)
{
	t_arguments *args;
	while(command_table)
	{
		if(command_table->command)
		if(check_wildcard(command_table->command))
			handle_command_wildcard(command_table);
		args = command_table->argument;
		while(args)
		{
			if(check_wildcard(args->arg))
			{
			args = handle_args_wildcard(command_table, args);
			continue;
			}
			args = args->next;
		}
		command_table = command_table->next;
	}
	return 1;
}

int expandline(t_line_processing_history *v_lines)
{
	int i;
	int flag;
	int redirection;
	char *line;

	i = 0;
	flag = 0;
	line = ft_strdup(v_lines->trimmed_line);
	if (start_error(line))
		return 0;

	while (line[i])
	{
		redirection = pipe_redirection(line[i], line[i + 1]);
		if (redirection == 4)
			if (herdoc_error(line, i))
				return 0;
		if (line[i] == '$')
			line = dollar_check(&i, v_lines, line);
		else if (line[i] == 34 || line[i] == 39)
			line = process_quotes(&i, v_lines, line);
		else if (whitespaces(line[i]))
			line = delete_spaces(line, i);
		else if (line[i] == '*')
			line[i] = (char)-1;
		if (!line)
			return 0;
		if (find_duplicate_redirections(line, i))
			return 0;
		if (redirection)
		{
			line = check_redirection_error(line, i, redirection);
			if (!line)
				return (0);
			if (!expanded_line_2_command_table(v_lines, get_last_pipe(&flag, line), redirection, ft_strdup(line)))
				return 0;
		}

		if (redirection == 10)
			v_lines->got_command_yet = 0;
		if (redirection == 4)
			i++;
		if (!line[i])
			break;
		i++;
	}

	if (!expanded_line_2_command_table(v_lines, get_last_pipe(&flag, line), 0, ft_strdup(line)))
		return 0;
	v_lines->expanded_line = line;
	return 1;
}

int expanded_line_2_command_table(t_line_processing_history *v_lines,
								  int start, int redirection_number, char *line)
{
	char *temp;
	int len;
	int start_iter;
	t_commandtable *command_table;
	int previous_redirection;

	start_iter = start;
	len = 0;
	previous_redirection = check_previous_redirection(line, start);
	while (!reached_a_redirection_or_end(line[start_iter]))
	{
		start_iter++;
		len++;
	}
	temp = line;
	line = ft_substr(line, start, len);
	free(temp);

	if (len && !is_full_of_whitespaces(line))
	{
		initialize_command_table_node(v_lines);
		command_table = get_last_command_line(v_lines->command_table);
		fill_command_type(command_table, previous_redirection);
		v_lines->is_next_a_command = 0;
		if (redirection_number == 10)
			command_table->pipe = 1;
		else if (redirection_number)
		{
			command_table->redirections = redirection_number;
			fill_is_a_command(v_lines, redirection_number);
		}
		split_into_table(line, command_table);
	}
	else
		fill_is_a_command(v_lines, redirection_number);
	free(line);
	return 1;
}

int parse(t_line_processing_history *v_lines)
{
	if (!expandline(v_lines))
		return 0;
	return (1);
}

void print_ct(t_line_processing_history *v_lines)
{
	t_commandtable *c_table;
	t_arguments *argi;
	c_table = v_lines->command_table;
	fflush(stdout);
	while (c_table)
	{
		printf("is command : %d, is a file_toWrite %d, is_herdoc %d, is append %d,file_toRead%d\n", c_table->is_a_command, c_table->is_a_file, c_table->is_heredoc, c_table->is_a_fileA, c_table->is_a_fileR);
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

void delete_table_node(t_commandtable *command_table)
{
	t_commandtable *previous_temp;
	t_commandtable *next_temp;
	
	previous_temp = command_table->previous;
	next_temp = command_table->next;
	if (command_table->command)
		free(command_table->command);
	if(command_table->limiter)
		free(command_table->limiter);
	free(command_table);
	if (previous_temp)
		previous_temp->next = next_temp;
	else
		v_lines->command_table = next_temp;
	if (next_temp)
		next_temp->previous = previous_temp;
}

int clean_nodes(t_commandtable *command_table)
{
	t_commandtable *temp;

	while (command_table)
	{
		temp = command_table->next;
		if (command_table->is_a_command == 0)
			delete_table_node(command_table);
		command_table = temp;
	}
	return 1;
}

void link_argument_nodes(t_commandtable *node_to_fill, t_commandtable *current_node)
{
	t_arguments *last_element;
	t_arguments *child_args_head;
	t_arguments *parent_args_head;

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

t_commandtable *get_table_after_pipe(t_commandtable *current_node)
{
	t_commandtable *command_table;

	command_table = current_node;
	while (command_table->previous)
	{
		if (command_table->previous->pipe == 1)
			break;
		command_table = command_table->previous;
	}
	return command_table;
}

void close_fds(t_commandtable *command_table)
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

t_commandtable *find_duplicate_files(t_commandtable *command_table)
{
	t_commandtable *duplicate;
	char *file_name;

	duplicate = 0;
	file_name = command_table->command;
	command_table = command_table->next;
	while (command_table)
	{
		if (command_table->is_a_fileA == 1 || command_table->is_a_file == 1)
		{
			if (command_table->previous)
			{
				if (command_table->previous->pipe == 1)
					break;
			}
			if (!ft_strncmp(command_table->command, file_name, max(ft_strlen(file_name), ft_strlen(command_table->command))))
			{
				duplicate = command_table;
			}
		}
		command_table = command_table->next;
	}
	return duplicate;
}

void handle_priority(t_commandtable *file1, t_commandtable *file2)
{
	int overwrite;

	overwrite = 0;
	if (file1->is_a_file || file2->is_a_file)
		overwrite = 1;
	if (overwrite)
	{
		file1->is_a_fileA = 0;
		file2->is_a_fileA = 0;
		file1->is_a_file = 1;
		file2->is_a_file = 1;
	}
}

void duplicate_files(t_commandtable *command_table)
{
	t_commandtable *duplicate;
	while (command_table)
	{
		if (command_table->is_a_fileA == 1 || command_table->is_a_file == 1)
		{
			duplicate = find_duplicate_files(command_table);
			if (duplicate)
				handle_priority(command_table, duplicate);
		}
		command_table = command_table->next;
	}
}

int open_all(t_commandtable *command_table)
{
	t_commandtable *head_node;
	int open_return;
	head_node = command_table;
	while (command_table)
	{
		if (command_table->is_a_file)
			open_return = file_opener(3, command_table->command, &command_table->self_input_fd, &command_table->self_output_fd);
		else if (command_table->is_a_fileA)
			open_return = file_opener(2, command_table->command, &command_table->self_input_fd, &command_table->self_output_fd);
		else if (command_table->is_a_fileR)
			open_return = file_opener(1, command_table->command, &command_table->self_input_fd, &command_table->self_output_fd);

		else if (command_table->is_heredoc)
			open_return = file_opener(0, command_table->limiter, &command_table->self_input_fd, &command_table->self_output_fd);
		command_table = command_table->next;
	}

	return (open_return);
}

t_commandtable *get_node_to_fill(t_commandtable *current_node)
{
	t_commandtable *node_to_fill;
	current_node = get_table_after_pipe(current_node);
	node_to_fill = current_node;
	while (current_node && current_node->pipe == 0)
	{
		if (current_node->is_a_command == 1)
		{
			node_to_fill = current_node;
			break;
		}
		if (current_node->next)
			current_node = current_node->next;
		else
			break;
	}
	if (current_node->is_a_command)
		node_to_fill = current_node;
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
	return (node_to_fill);
}

void transfer_node_infos(t_commandtable *node_to_fill, t_commandtable *current_node)
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

int built_in_check(char *line)
{

	if (!ft_strncmp("cd", line, max(ft_strlen(line), ft_strlen(""))))
		return 11;
	else if (!ft_strncmp("export", line, max(ft_strlen(line), ft_strlen(""))))
		return 13;
	else if (!ft_strncmp("unset", line, max(ft_strlen(line), ft_strlen(""))))
		return 14;
	else if (!ft_strncmp("exit", line, max(ft_strlen(line), ft_strlen(""))))
		return 15;
	else
		return 0;
}

int is_built_in(t_line_processing_history *v_lines)
{
	t_commandtable *command_table;
	t_commandtable *command;
	int i;
	int is_built_in;

	is_built_in = 0;
	i = 0;
	command_table = v_lines->command_table;

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

void execute_built_in()
{
	printf("execute built_in\n");
}

int process_command_table(t_line_processing_history *v_lines)
{
	t_commandtable *node_to_fill;
	t_commandtable *current_node;
	int built_in_number;

	current_node = v_lines->command_table;
	duplicate_files(current_node);

	// if built in// execute it/ then fork and make it work in the child process as well
	built_in_number = is_built_in(v_lines);
	
	signal(SIGINT, &in_herdoc);
	v_lines->parent_id = fork();
	if (v_lines->parent_id != 0)
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
		execute_built_in();
		return 0;
	}
	signal(SIGINT, SIG_DFL);

	if (open_all(current_node) == 0)
		return 0;
	while (current_node)
	{
		node_to_fill = get_node_to_fill(current_node);
		if (current_node != node_to_fill)
		{
			transfer_node_infos(node_to_fill, current_node);
		}
		current_node = current_node->next;
	}
	clean_nodes(v_lines->command_table);
	process_wildcards(v_lines->command_table);
	return 1;
}

int processline(t_line_processing_history *v_lines)
{
	int parse_success;

	v_lines->trimmed_line = ft_strtrim(v_lines->entered_line, " 		");
	if (!ft_strncmp(v_lines->trimmed_line, "exit", max(ft_strlen(v_lines->trimmed_line), 4)))
	{
		handle_exit();
	}
	parse_success = parse(v_lines);
	if (parse_success)
		parse_success = process_command_table(v_lines);
	if (parse_success)
	{
		print_ct(v_lines);
		// syntax_check();
		// execute();//talk bout if theres smth that needs to go back here in the parsin
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{

	v_lines = malloc(sizeof(t_line_processing_history));
	initialize_v_lines(v_lines, env);
	handle_signals();

	struct termios oldtio;
	struct termios newtio;

	tcgetattr(0, &oldtio);
	v_lines->terminal_settings = oldtio;
	oldtio.c_lflag &= ~ICANON;
	oldtio.c_lflag &= ECHO;
	tcsetattr(0, TCSANOW, &oldtio);

	while (1)
	{
		handle_signals();
		v_lines->entered_line = readline("bash tsetta -0.1 $ ");

		if (!v_lines->entered_line)
			handle_exit();

		if (!is_full_of_whitespaces(v_lines->entered_line))
		{
			processline(v_lines);
			add_history(v_lines->entered_line);
		}
		if (v_lines->parent_id != 0)
		{
			wait(NULL);
		}
		else
		{
			close_fds(v_lines->command_table);
			free_all(v_lines);
			free_env(v_lines->env_vars);
			return 1;
		}

		free_all(v_lines);
	}
	return 1;
}
