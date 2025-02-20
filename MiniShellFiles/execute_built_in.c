/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:22:57 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/20 15:23:22 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_in_parent(int built_in_number)
{
	if (!g_v_lines->command_table->next)
	{
		if (built_in_number == 11)
			ft_cd();
		else if (built_in_number == 13 && g_v_lines->command_table->argument)
			ft_export(g_v_lines->command_table->argument);
		else if (built_in_number == 14)
			ft_unset();
		else if (built_in_number == 15)
			ft_exit(g_v_lines->command_table->argument);
	}
}

void	execute_built_in_first_child(int built_in_number)
{
	if (!g_v_lines->command_table->next)
	{
		dup2(g_v_lines->command_table->output_fd, 1);
		if (built_in_number == 13 && !g_v_lines->command_table->argument)
			ft_export(g_v_lines->command_table->argument);
		else if (built_in_number == 12)
			ft_pwd();
		else if (built_in_number == 16)
			ft_env();
		else if (built_in_number == 17)
			ft_echo(g_v_lines->command_table->argument);
	}
}

void	execute_built_in_child(int built_in_number, t_arguments *args)
{
	if (built_in_number == 11)
		ft_cd();
	else if (built_in_number == 13)
		ft_export(g_v_lines->command_table->argument);
	else if (built_in_number == 12)
		ft_pwd();
	else if (built_in_number == 14)
		ft_unset();
	else if (built_in_number == 15)
		ft_exit(args);
	else if (built_in_number == 16)
		ft_env();
	else if (built_in_number == 17)
		ft_echo(args);
}
