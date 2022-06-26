/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:52:11 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 12:52:12 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(void)
{
	printf("exit\n");
	free_env(g_v_lines->env_vars);
	free_all(g_v_lines);
	tcsetattr(0, TCSANOW, &g_v_lines->terminal_settings);
	system("leaks minishell");
	exit(g_v_lines->exit_status);
}