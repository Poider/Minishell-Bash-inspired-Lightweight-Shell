/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:54:26 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:35 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	all_join(t_parsing_path_var	*var, char *commande)
{
	var->i = 0;
	while (var->arr[var->i])
	{
		var->arr[var->i] = ft_strjoin(var->arr[var->i], "/");
		var->i++;
	}
	var->i = 0;
	while (var->arr[var->i])
	{
		var->arr[var->i] = ft_strjoin(var->arr[var->i], commande);
		var->i++;
	}
}

char	**parsing_path(char *commande)
{
	t_parsing_path_var	var;

	if (!ft_strlen(commande))
	{
		var.arr = ft_split(",", ',');
		return (var.arr);
	}	
	var.head = g_v_lines->env_vars_head;
	while (var.head)
	{
		if (!ft_strncmp(var.head->key, "PATH", \
			max(ft_strlen(var.head->key), ft_strlen("PATH"))))
			var.path = var.head->value;
		var.head = var.head->next;
	}
	if (!var.path)
	{
		g_v_lines->exit_status = 1;
		handle_exit();
	}
	var.arr = ft_split(var.path, ':');
	all_join(&var, commande);
	return (var.arr);
}

void	flag_equal_zero(t_correct_access_var *var)
{
	if (var->args)
	{
		var->a[0] = var->path[var->i];
		while (var->args)
		{
			var->a[var->j] = var->args->arg;
			var->args = var->args->next;
			var->j++;
		}
		var->a[var->j] = NULL;
	}
	else
	{
		var->a[0] = var->path[var->i];
		var->a[1] = NULL;
	}
	var->found = 1;
	if ((execve(var->path[var->i], var->a, NULL)) == -1)
	{
		perror("execve");
		exit(126);
	}
}

void	free_arr(t_correct_access_var *var)
{
	var->i = 0;
	while (var->a[var->i] != NULL)
	{
		free(var->a[var->i]);
		var->i++;
	}
	free(var->a);
}

void	correct_access(t_commandtable *command_table)
{
	t_correct_access_var	var;

	var.j = 1;
	var.i = 0;
	var.found = 0;
	var.args = command_table->argument;
	var.a = malloc((ft_lstsize(var.args) + 2) * sizeof(char *));
	var.path = parsing_path(command_table->command);
	while (var.path[var.i])
	{
		var.flag = access(var.path[var.i], X_OK);
		if (var.flag == 0)
		{
			flag_equal_zero(&var);
			free_arr(&var);
		}
		var.i++;
	}
	if (!var.found)
	{
		printf("bash tsetta: %s: command not found\n", command_table->command);
		exit(127);
	}
}
