/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:58:57 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 13:35:27 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	norm_old_pwd(t_list	*head, char *old_directory)
{
	if (!(ft_strncmp(head->key, "OLDPWD", \
		max(6, ft_strlen(head->key)))))
	{
		if (head->value)
			free (head->value);
		head->value = old_directory;
	}
}

void	old_pwd_env(char *old_directory)
{
	char	*new_old_pwd;
	char	str[10000];
	char	*current_directory;
	t_list	*head ;

	new_old_pwd = NULL;
	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!(ft_strncmp(head->key, "PWD", \
			max(ft_strlen(head->key), 3))))
		{
			new_old_pwd = head->value;
			current_directory = getcwd(str, 100);
			if (current_directory)
				current_directory = ft_strdup(current_directory);
			if (new_old_pwd)
				free (new_old_pwd);
			head->value = current_directory;
		}
		norm_old_pwd(head, old_directory);
		head = head->next;
	}
}

char	*cd_home(void)
{
	t_list	*head;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(head->key, "HOME", \
			max(ft_strlen(head->key), ft_strlen("HOME"))))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	cd_norm(int *flag, t_arguments *args)
{
	*flag = 0;
	if (args == NULL)
	{
		*flag = chdir(cd_home());
		if (*flag == -1)
		{
			g_v_lines->failure = 1;
			perror("chdir");
		}
	}
	else if (args->arg[0] == '~' && ft_strlen(args->arg) == 1)
	{
		*flag = chdir(cd_home());
		if (*flag == -1)
		{
			g_v_lines->failure = 1;
			perror("cd");
		}
	}
	else if (chdir(args->arg) == -1)
	{
		g_v_lines->failure = 1;
		perror("cd");
		*flag = -1;
	}
}

void	ft_cd(void)
{
	t_arguments	*args;
	int			flag;
	char		str[100];
	char		*p;

	flag = 0;
	p = getcwd(str, 100);
	args = g_v_lines->command_table->argument;
	cd_norm(&flag, args);
	if (flag != -1)
		old_pwd_env(ft_strdup(p));
}
