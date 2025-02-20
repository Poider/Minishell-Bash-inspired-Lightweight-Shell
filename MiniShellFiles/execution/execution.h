/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:54:34 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 14:32:12 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../minishell.h"

typedef struct s_commandtable				t_commandtable;
typedef struct s_arguments					t_arguments;
typedef struct s_line_processing_history	t_line_processing_history;

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}		t_list;

typedef struct s_exit
{
	t_arguments	*args_temp;
	int			digit_arg;
	int			count_arg;
	int			nb;
}	t_exit;

typedef struct s_export_sort_var
{
	char	**arr;
	int		env_var_numb;
	int		i;
	char	*tmp;
	int		j;
}	t_export_sort_var;

typedef struct s_export
{
	t_list		*new_arg;
	t_list		*head;
	char		**arr;
	int			env_number;
	int			i;
	int			type;
	int			equal;
	char		*new_second_half;
	char		*line;
	char		*old_second;
	int			check_error;
	char		*new_second;
	char		*temp2;
}	t_export;

typedef struct s_with_path_var
{
	char			*back_slash;
	int				i;
	int				j;
	int				can_access;
	t_arguments		*args;
	char			**a;
}	t_with_path_var;

typedef struct s_parsing_path_var
{
	char	**arr;
	char	*path;
	t_list	*head;
	int		i;
	int		flag;
}	t_parsing_path_var;

typedef struct s_correct_access_var
{
	t_arguments	*args;
	char		**path;
	int			flag;
	int			j;
	int			i;
	char		**a;
	int			built_in_number;
	int			found;
}	t_correct_access_var;

typedef struct s_execute_var
{
	t_commandtable	*command_table;
	char			**args;
	int				fd[2];
	int				pipe_save;
	int				out;
	int				built_in_number;
	int				can_access;
	int				j;
	int				i;
}	t_execute_var;

typedef struct s_env_var_list
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*new_node;
	int		env_vars_count;
	int		i;
}	t_env_var_list;

/*builtins*/
void	exec(void);
void	ft_pwd(void);
void	ft_env(void);
void	ft_cd(void);
void	ft_unset(void);
void	ft_exit(t_arguments *args);
void	ft_export(t_arguments *args);
void	ft_echo(t_arguments	*args);
int		n_arg_check(t_arguments *args);
int		is_built_in(t_line_processing_history *g_v_lines);
void	execute_built_in_child(int built_in_number, t_arguments *args);
int		built_in_check(char *line);
char	*first_half(char *str);
char	*second_half(char *str);
int		args_types(char *str);

/*export_utils*/
int		env_numb(t_list *head);
char	**sort(t_list *head);
void	print_env(char *arr);
int		args_types(char *str);
int		is_higher(char *str1, char *str2);
int		check_error_of_first_half(char *str);
char	*old_second_half_export_plus(char *arg);
char	*first(char *str);
int		arg_exist(char *arg);
void	eplace_arg_value(char *second, char *first);
char	*first_half_for_export_plus(char *str);
void	replace_second_half_export_plus(char *old_second, char *first_half_var);
void	replace_arg_value(char *second, char *first);

/*exec_utils*/
char	**args_to_table(t_arguments *args);
int		number_of_commands(t_commandtable *command_table);
int		commande_with_path(t_commandtable *commande);
char	**parsing_path(char *commande);
void	correct_access(t_commandtable *command_table);
int		execute(t_line_processing_history *g_v_lines);
void	access_negative(t_commandtable *commande);
void	all_join(t_parsing_path_var	*var, char *commande);
void	flag_equal_zero(t_correct_access_var *var);
void	free_arr(t_correct_access_var *var);

/*libft*/
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		count_string2(const char *str, char c);
char	*ft_strdup(const char *s1);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
int		string_size1(const char *str, char c);
char	**t(char **arr, char c, const char *s);
int		exit_atoi(const char *s);

/*pipe*/
char	**parsing_path(char *command);
void	correct_access(t_commandtable *command_table);
int		commande_with_path(t_commandtable *commande);
int		execute(t_line_processing_history *g_v_lines);

/*liked_list*/
t_list	*ft_lstnew(char *first, char *second);
void	ft_lstadd_back(t_list *head, t_list *new);
t_list	*del_node(t_list *list_head, t_list *node_2_delete);
void	ft_lstadd_back1(t_list **head, t_list *new);
int		ft_lstsize(t_arguments *lst);

/*env*/
void	free_env_value(t_list *node);
char	**duplicate_envirement_var(char **env);
char	*first_half(char *str);
char	*second_half(char *str);
void	old_pwd_clear(t_list *head);
t_list	*env_vars_list(char **env);
#endif
