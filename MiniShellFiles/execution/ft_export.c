/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:35:27 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:46:08 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	without_args(t_export *var)
{
	var->env_number = env_numb(var->head);
	var->arr = sort(var->head);
	while (var->i < var->env_number)
		print_env(var->arr[var->i++]);
	free(var->arr);
}

void	type_1(t_export	*var, t_arguments *args)
{
	var->check_error = check_error_of_first_half(first_half(args->arg));
	var->equal = arg_exist(first_half(args->arg));
	if (var->equal == 1 && var->check_error == 1)
	{
		var->new_arg = ft_lstnew(first_half(args->arg), \
			second_half(args->arg));
		ft_lstadd_back1(&g_v_lines->env_vars_head, var->new_arg);
	}
	else if (var->equal == 0 && var->check_error == 1)
		replace_arg_value(second_half(args->arg), \
	first_half(args->arg));
}

void	type_2(t_export	*var, t_arguments *args)
{
	var->equal = arg_exist(first_half_for_export_plus(args->arg));
	var->check_error = check_error_of_first_half \
		(first_half_for_export_plus(args->arg));
	if (var->equal == 1 && var->check_error == 1)
	{
		var->new_arg = ft_lstnew(first_half_for_export_plus(args->arg), \
			second_half(args->arg));
		ft_lstadd_back1(&g_v_lines->env_vars_head, var->new_arg);
	}
	else if (var->equal == 0 && var->check_error == 1)
	{
		var->old_second = old_second_half_export_plus \
			(first_half_for_export_plus(args->arg));
		var->new_second = second_half(args->arg);
		var->temp2 = var->old_second;
		var->old_second = ft_strjoin(var->old_second, var->new_second);
		replace_second_half_export_plus(var->old_second, \
			first_half_for_export_plus(args->arg));
		free(var->new_second);
		free(var->temp2);
	}
}

void	type_3(t_export	*var, t_arguments *args)
{
	var->check_error = check_error_of_first_half(first(args->arg));
	var->equal = arg_exist(first(args->arg));
	if (var->equal == 1 && var->check_error == 1)
	{
		var->new_arg = ft_lstnew(first(args->arg), NULL);
		ft_lstadd_back1(&g_v_lines->env_vars_head, var->new_arg);
	}
}

void	ft_export(t_arguments *args)
{
	t_export	var;

	var.i = 0;
	var.head = g_v_lines->env_vars_head;
	if (!args)
		without_args(&var);
	while (args)
	{
		var.type = args_types(args->arg);
		if (var.type == 0)
		{
			printf("export: '%s': not a valid identifier\n", args->arg);
			g_v_lines->failure = 1;
		}
		else if (var.type == 3)
			type_3(&var, args);
		else if (var.type == 1)
			type_1(&var, args);
		else if (var.type == 2)
			type_2(&var, args);
		args = args->next;
	}
}

//	if(!args) //if we have just command
//else if(var.type == 3) //without second_half
//else if(var.type == 1) //=
//else if(var.type == 2) //+=