/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:22:57 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:33 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**args_to_table(t_arguments *args)
{
	char	**args_array;
	int		size;
	int		i;

	size = ft_lstsize(args);
	args_array = malloc(sizeof(char *) * (size + 1));
	args_array[size] = 0;
	i = 0;
	while (i < size)
	{
		args_array[i] = args->arg;
		args = args->next;
		i++;
	}
	return (args_array);
}

int	number_of_commands(t_commandtable *command_table)
{
	int	i;

	i = 0;
	while (command_table)
	{
		i++;
		command_table = command_table->next;
	}
	return (i);
}

void	access_equal_zero(t_commandtable *commande, t_with_path_var	*var)
{
	var->a = malloc((ft_lstsize(var->args) + 2) * sizeof(char *));
	if (var->args)
	{
		while (var->a[var->j] && var->args)
		{
			var->a[0] = var->back_slash;
			var->a[var->j] = var->args->arg;
			var->j++;
			var->args = var->args->next;
		}
		var->a[var->j] = NULL;
	}
	else
	{
		var->a[0] = var->back_slash;
		var->a[1] = NULL;
	}
	if ((execve(commande->command, var->a, NULL)) == -1)
	{
		perror("execve");
		exit(126);
	}
	free(var->a);
}

void	access_negative(t_commandtable *commande)
{
	printf("bash tsetta: %s: No such file or directory\n", commande->command);
	exit(127);
}

int	commande_with_path(t_commandtable *commande)
{
	t_with_path_var	var;

	var.i = 0;
	var.j = 1;
	var.args = g_v_lines->command_table->argument;
	var.back_slash = ft_strchr(commande->command, '/');
	if (var.back_slash == NULL)
		return (0);
	else
		var.can_access = access(commande->command, F_OK);
	while (var.back_slash[var.i])
		var.i++;
	if (var.back_slash[var.i - 1] == '/')
	{
		printf("bash tsetta: %s: Not a directory\n", var.back_slash);
		exit(126);
	}
	if (var.can_access == 0)
		access_equal_zero(commande, &var);
	if (var.can_access == -1)
		access_negative(commande);
	return (var.can_access);
}
