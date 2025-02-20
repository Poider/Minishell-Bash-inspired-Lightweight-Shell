/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:39:21 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 17:56:55 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "./executionn/execution.h"

typedef struct s_commandtable				t_commandtable;
typedef struct s_arguments					t_arguments;
typedef struct s_line_processing_history	t_line_processing_history;
typedef struct s_list						t_list;
t_line_processing_history					*g_v_lines;
typedef struct s_iters1
{
	int	i;
	int	j;
	int	len;
}				t_iters1;

typedef struct s_iters2
{
	int	start_position;
	int	redirection_number;
}				t_iters2;

typedef struct s_iters3
{
	int	redirection;
	int	j;
	int	previous_redirection;
}				t_iters3;

typedef struct s_iters4
{
	int		i;
	int		flag;
	int		redirection;
	char	*line;
}				t_iters4;

typedef struct s_iters5
{
	char			*temp;
	int				len;
	int				start_iter;
	t_commandtable	*command_table;
	int				previous_redirection;
}				t_iters5;

typedef struct s_iters6
{
	char	*token;
	char	*temp;
}				t_iters6;

typedef struct s_iters8
{
	char	*temp_joined;
	char	*joined;
	char	*side_1;
	char	*side_2;
	char	*var_value;
}				t_iters8;

typedef struct s_iters9
{
	t_commandtable	*node_to_fill;
	t_commandtable	*current_node;
	int				built_in_number;
}				t_iters9;

typedef struct s_iters10
{
	int		fd[2];
	char	*line;
	char	newliney;
}				t_iters10;

typedef struct s_iters7
{
	int		i;
	char	*temp;
	char	*side_1;
	char	*side_2;
	char	*middle_stuff;
	char	*joined;
	int		quote_type;
}				t_iters7;

typedef struct s_dir_match_var
{
	DIR				*directory;
	struct dirent	*entity;
	char			*matched_names;
	t_arguments		*args;
	t_arguments		*args_return;
}				t_dir_match_var;

typedef struct s_arguments
{
	char				*arg;
	struct s_arguments	*next;
	struct s_arguments	*previous;

}				t_arguments;

typedef struct s_commandtable
{
	char					*command;
	t_arguments				*argument;
	int						input_fd;
	int						output_fd;
	int						self_input_fd;
	int						self_output_fd;
	int						is_a_command;
	int						is_a_file;
	int						is_a_file_r;
	int						is_a_file_a;
	int						is_heredoc;
	char					*limiter;
	int						quote_in_limiter;
	int						pipe;
	int						redirections;
	struct s_commandtable	*next;
	struct s_commandtable	*previous;
}				t_commandtable;

typedef struct s_line_processing_history
{
	int					failure;
	t_list				*env_vars_head;
	struct sigaction	sa;
	int					got_command_yet;
	pid_t				*process_id;
	int					iterator;
	int					commands_number;
	char				**env_vars;
	int					exit_status;
	t_commandtable		*command_table;
	int					*current_pipe;
	int					redisplayer;
	int					is_next_a_command;
	pid_t				parent_id;
	char				*entered_line;
	char				*trimmed_line;
	char				*dollar_processed;
	char				*expanded_line;
	struct termios		terminal_settings;
}				t_line_processing_history;

int				ft_tolower(int a);
char			**ft_split_whitespaces(char *str);
t_arguments		*match_with_directory(char *pattern);
void			close_fds(t_commandtable *command_table);
int				reached_a_redirection_or_end(char c);
int				is_full_of_whitespaces(char *line);
int				processline(t_line_processing_history *g_v_lines);
void			print_ct(t_line_processing_history *g_v_lines);
int				syntax_check(t_commandtable *commandtable);
int				parse(t_line_processing_history *g_v_lines);
int				expanded_line_2_command_table(
					t_line_processing_history *g_v_lines,
					int start, int redirection_number, char *line);
int				expandline(t_line_processing_history *g_v_lines);
int				get_last_pipe(int *flag, char *line);
int				pipe_redirection(char c, char after_c);
char			*number_to_redirection(int c);
char			*dollar_check(int *index,
					t_line_processing_history *g_v_lines, char *line);
char			*expand_dollar(char *line,
					int var_start, int var_len, int type);
char			*get_var(char *var);
char			*delete_spaces(char *line, int start_eliminating);
int				check_pipe_error(char *line, int i);
char			*process_quotes(int *index,
					t_line_processing_history *g_v_lines, char *line);
char			*process_single_quotes(char *line,
					int *end_quote, t_line_processing_history *g_v_lines);
char			*process_double_quotes(char *line,
					int *end_quote, t_line_processing_history *g_v_lines);
void			unclosed_quotes(void);
int				split_into_table(char *line, t_commandtable *command_table);
t_arguments		*get_last_argument(t_arguments *argument);
void			initialize_argument_node(t_commandtable *command_table);
void			fill_limiter(char *line, t_commandtable *command_table);
void			fill_file(char *line, t_commandtable *command_table);
void			fill_command(char *line, t_commandtable *command_table);
void			fill_arguments(t_commandtable *command_table,
					char *line, int *index);
char			*clean_token(char *line, int *iteration_position);
char			*delete_quote(char *token, int *start_quote_position);
int				file_opener(int permission,
					char *file_name, int *read_fd, int *write_fd);
int				make_herdoc_pipe(char *limiter, int permission);
void			free_all(t_line_processing_history *g_v_lines);
int				whitespaces(char c);
int				initialize_command_table_node(
					t_line_processing_history *g_v_lines);
t_commandtable	*get_last_command_line(t_commandtable *command_table);
void			initialize_command_infos(t_commandtable *command_table);
char			*check_redirection_error(char *line, int i, int redirection);
char			*redirection_error(char *line, int i);
char			*pipe_error(char *line, int i);
void			free_command_table(t_commandtable *command_table);
void			free_command_table_content(t_commandtable *command_table);
void			free_arguments(t_arguments *argument);
void			null_command_table_arguments(t_commandtable *command_table);
int				handle_signals(void);
void			exiting(int signum);
void			get_parent_id(int signum, siginfo_t *siginfo, void *noUse);
void			ctrl_backslash_handler(int signum);
void			ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse);
int				max(int a, int b);
int				fill_command_type(t_commandtable *command_table, int type);
int				fill_is_a_command(t_line_processing_history *g_v_lines,
					int redirection_number);
int				handle_exit(void);
int				initialize_v_lines(t_line_processing_history *g_v_lines,
					char **env);
int				null_lines(t_line_processing_history *g_v_lines);
int				free_lines(t_line_processing_history *g_v_lines);
char			*to_lower(char *str);
int				ft_tolower(int a);
int				process_command_table(t_line_processing_history *g_v_lines);
void			free_env(char **arr);
int				herdoc_error(char *line, int i);
int				find_duplicate_redirections(char *line, int i);
int				start_error(char *line);
int				check_previous_redirection(char *line, int start);
t_commandtable	*get_node_to_fill(t_commandtable *current_node);
void			duplicate_files(t_commandtable *command_table);
int				is_built_in(t_line_processing_history *g_v_lines);
int				open_all(t_commandtable *command_table);
int				process_wildcards(t_commandtable *command_table);
void			delete_arg_node(t_commandtable *command_table,
					t_arguments *arg_to_delete);

void			execute_built_in_parent(int built_in_number);
void			execute_built_in_first_child(int built_in_number);
void			execute_built_in_child(int built_in_number, t_arguments *args);
t_list			*env_vars_list(char **env);
void			free_env_list(void);
int				readline_loop(t_line_processing_history *g_v_lines);

//signals
void			ctrl_c_handler(int signum, siginfo_t *siginfo, void *noUse);
void			in_herdoc(int signum);
void			ctrl_backslash_handler(int signum);
void			get_parent_id(int signum, siginfo_t *siginfo, void *noUse);
int				handle_signals(void);
void			link_argument_nodes(t_commandtable *node_to_fill,
					t_commandtable *current_node);
void			execute_built_in(int built_in_number);

//helpers
int				numbcount(int n);
char			*ft_itoa(int n);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
int				ft_isalnum(int c);

//split
char			**ft_split_whitespaces(char *str);
#endif