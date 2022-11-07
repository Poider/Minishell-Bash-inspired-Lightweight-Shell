/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:47 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:56 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	env_numb(t_list *head)
{
	int	env_var_numb;

	env_var_numb = 0;
	while (head)
	{
		head = head->next;
		env_var_numb++;
	}
	return (env_var_numb);
}

void	put_key(t_export_sort_var	*var, t_list *head)
{
	while (var->i < var->env_var_numb)
	{
		var->arr[var->i] = head->key;
		var->i++;
		head = head->next;
	}
}

char	**sort(t_list *head)
{
	t_export_sort_var	var;

	var.i = 0;
	var.env_var_numb = env_numb(head);
	var.arr = malloc(sizeof(char *) * (var.env_var_numb + 1));
	put_key(&var, head);
	head = g_v_lines->env_vars_head;
	var.i = 1;
	while (var.i < var.env_var_numb)
	{
		var.j = 0;
		while (var.j < var.env_var_numb - 1)
		{
			if (is_higher(var.arr[var.j], var.arr[var.j + 1]))
			{
				var.tmp = var.arr[var.j];
				var.arr[var.j] = var.arr[var.j + 1];
				var.arr[var.j + 1] = var.tmp;
			}
			var.j++;
		}
		var.i++;
	}
	return (var.arr);
}

void	print_env(char *arr)
{
	t_list	*head;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(arr, head->key, \
			max(ft_strlen(arr), ft_strlen(head->key))))
		{
			if (head->value)
				printf("declare -x %s=\"%s\" \n", head->key, head->value);
			else
				printf("declare -x %s\n", head->key);
		}
		head = head->next;
	}
}

int	args_types(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && str[i - 1] != '+')
			return (1);
		else if (str[i - 1] == '+' && str[i] == '=')
			return (2);
		i++;
	}
	return (3);
}

//return (3);//if !exists add with null otherwise noth