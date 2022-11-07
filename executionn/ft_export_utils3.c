/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:02:34 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:46:03 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_higher(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, max(ft_strlen(str1), ft_strlen(str2))) > 0)
		return (1);
	return (0);
}

int	check_error_of_first_half(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			g_v_lines->failure = 1;
			printf("export: '%s': not a valid identifier\n", str);
			{
				free(str);
				return (0);
			}
			break ;
		}
		i++;
	}
	free(str);
	return (1);
}

char	*old_second_half_export_plus(char *arg)
{
	t_list	*head;
	char	*old_second;

	head = g_v_lines->env_vars_head;
	while (head)
	{
		if (!ft_strncmp(head->key, arg, \
			max(ft_strlen(head->key), ft_strlen(arg))))
			old_second = head->value;
		head = head->next;
	}
	free(arg);
	return (old_second);
}
