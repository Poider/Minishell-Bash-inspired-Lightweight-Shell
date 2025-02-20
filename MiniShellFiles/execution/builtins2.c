/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:56:45 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:19 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_pwd(void)
{
	char	str[10000];
	char	*p;

	p = getcwd(str, 100);
	if (!p)
	{
		perror("getcwd() error");
		g_v_lines->failure = 1;
	}
	else
	{
		g_v_lines->exit_status = 0;
		printf("%s\n", str);
	}
}

void	ft_env(void)
{
	t_list	*head;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (head->value)
		{
			printf("%s=", head->key);
			printf("%s", head->value);
			printf("\n");
		}
		head = head->next;
	}
}

void	ft_unset(void)
{
	t_arguments	*args;
	t_list		*head;

	args = g_v_lines->command_table->argument;
	while (args)
	{
		head = g_v_lines->env_vars_head;
		while (head)
		{
			if (!ft_strncmp(args->arg, head->key, \
				max(ft_strlen(args->arg), ft_strlen(head->key))))
			{
				head = del_node(g_v_lines->env_vars_head, head);
				continue ;
			}
			head = head->next;
		}
		args = args->next;
	}
}

int	n_arg_check(t_arguments *args)
{
	int	i;

	i = 1;
	if (!args)
		return (0);
	if (args->arg[0] == '-' && args->arg[1] != 0)
	{
		while (args->arg[i])
		{
			if (args->arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_arguments *args)
{
	int	n_flag;
	int	new_line;

	n_flag = 1;
	new_line = 1;
	while (n_flag == 1)
	{
		n_flag = n_arg_check(args);
		if (n_flag == 1)
			new_line = 0;
		if (n_flag == 1)
		args = args->next;
	}
	while (args)
	{
		write(1, args->arg, ft_strlen(args->arg));
		if (args->next)
			write(1, " ", 1);
		args = args->next;
	}
	if (new_line == 1)
		write(1, "\n", 1);
	g_v_lines->exit_status = 0;
}

	//n_flag = 1; // if optin -n exist
	//new_line = 1; // if new_line exist