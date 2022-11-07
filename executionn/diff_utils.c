/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:55:41 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:23 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_env_value(t_list *node)
{
	free(node->value);
	node->value = 0;
}

char	**duplicate_envirement_var(char **env)
{
	int		env_vars_count;
	char	**array;
	int		i;

	i = 0;
	env_vars_count = 0;
	while (env[env_vars_count])
		env_vars_count++;
	array = malloc(sizeof(char *) * (env_vars_count + 1));
	while (i < env_vars_count)
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	array[i] = 0;
	return (array);
}

char	*first_half(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (str[i] != '=' && str[i])
		i++;
	p = ft_substr(str, 0, i);
	return (p);
}

char	*second_half(char *str)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			p = ft_substr(str, i + 1, ft_strlen(str));
			break ;
		}
		i++;
	}
	return (p);
}

void	old_pwd_clear(t_list *head)
{
	while (head)
	{
		if (!(ft_strncmp(head->key, "OLDPWD", ft_strlen("OLDPWD"))))
		{
			if (head->value)
				free(head->value);
			head->value = NULL;
		}
		head = head->next;
	}
}
