/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:29:07 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:45:29 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_list	*env_vars_list(char **env)
{
	t_env_var_list	var;

	var.tmp = NULL;
	var.i = 1;
	var.env_vars_count = 0;
	while (env[var.env_vars_count])
		var.env_vars_count++;
	if (var.env_vars_count)
	{
		var.lst = ft_lstnew(first_half(env[0]), second_half(env[0]));
		var.tmp = var.lst;
		while (var.i < var.env_vars_count)
		{
			var.new_node = ft_lstnew(first_half(env[var.i]), \
				second_half(env[var.i]));
			ft_lstadd_back1(&var.lst, var.new_node);
			var.lst = var.lst->next;
			var.i++;
		}
	}
	var.lst = var.tmp;
	old_pwd_clear(var.lst);
	return (var.tmp);
}
