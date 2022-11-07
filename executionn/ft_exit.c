/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:01:21 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 14:46:57 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	arg_is_digit_or_not(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	norm_exit_count_one(t_arguments *args, t_exit *var)
{
	if (var->count_arg == 1)
	{
		if (var->digit_arg == 1)
		{
			var->nb = exit_atoi(args->arg);
			g_v_lines->exit_status = var->nb % 256;
			printf("exit\n");
			handle_exit();
		}
		else if (var->digit_arg == 0)
		{
			g_v_lines->exit_status = 255;
			printf("exit\n");
			printf("bash tsetta -0.1: exit: %s: numeric \
argument required\n", args->arg);
			handle_exit();
		}
	}
}

void	norm_exit_count_big_of_one(t_arguments *args, t_exit *var)
{
	if (var->count_arg > 1)
	{
		if (var->digit_arg == 1)
		{
			g_v_lines->failure = 1;
			printf("exit\n");
			printf("bash tsetta -0.1: exit: \
too many arguments\n");
		}
		else
		{
			g_v_lines->exit_status = 255;
			printf("exit\n");
			printf("bash tsetta -0.1: exit: %s:\
numeric argument required\n", args->arg);
			handle_exit();
		}
	}
}

void	ft_exit(t_arguments *args)
{
	t_exit	var;

	var.args_temp = args;
	var.digit_arg = 0;
	var.count_arg = 0;
	if (args)
	var.digit_arg = arg_is_digit_or_not(args->arg);
	while (var.args_temp)
	{
		var.args_temp = var.args_temp->next;
		var.count_arg++;
	}
	norm_exit_count_one(args, &var);
	norm_exit_count_big_of_one(args, &var);
}
