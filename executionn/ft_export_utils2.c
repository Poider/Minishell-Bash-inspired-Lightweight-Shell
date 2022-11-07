/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:41 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:46:00 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*first(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (str[i])
		i++;
	p = ft_substr(str, 0, i);
	return (p);
}

int	arg_exist(char *arg)
{
	t_list	*head;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(head->key, arg, \
			max(ft_strlen(head->key), ft_strlen(arg))))
		{
			free(arg);
			return (0);
		}
		head = head->next;
	}
	free(arg);
	return (1);
}

void	replace_arg_value(char *second, char *first)
{
	t_list		*head;
	t_arguments	*args;

	args = g_v_lines->command_table->argument;
	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(head->key, first, \
			max(ft_strlen(head->key), ft_strlen(first))))
		{
			if (head->value)
				free(head->value);
			head->value = second;
		}
		head = head->next;
	}
	free(first);
}

char	*first_half_for_export_plus(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (str[i] != '=')
		i++;
	p = ft_substr(str, 0, i - 1);
	return (p);
}

void	replace_second_half_export_plus(char *old_second, char *first_half_var)
{
	t_list			*head;
	t_arguments		*args;

	head = g_v_lines->env_vars_head;
	args = g_v_lines->command_table->argument;
	while (head)
	{
		if (!ft_strncmp(head->key, first_half_var, \
			max(ft_strlen(head->key), ft_strlen(first_half_var))))
		{
			head->value = old_second;
		}
		head = head->next;
	}
	free(first_half_var);
}

//return (0); //  equal
//return (1); // not equal