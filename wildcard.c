/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:15:26 by mel-amma          #+#    #+#             */
/*   Updated: 2022/03/04 13:33:11 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_more_letters(char *pattern)
{
	int	i;

	i = 0;
	if (pattern[0] == 0)
		return (FALSE);
	while (pattern[i])
	{
		if (pattern[i] != -1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	match(char *text, char *pattern)
{
	if (!ft_strncmp(text, pattern, PATH_MAX))
		return (TRUE);
	else if (pattern[0] == 0 || text[0] == 0)
	{
		if (no_more_letters(pattern))
			return (TRUE);
		else
			return (FALSE);
	}
	if (pattern[0] == -1)
		return (match(text + 1, pattern) || match(text, pattern + 1));
	else if (pattern[0] == text[0])
		return (match(text + 1, pattern + 1));
	else
		return (FALSE);
}

int	before_matching(char *text, char *pattern)
{
	if (text[0] == 0 && pattern[0] != 0)
		return (0);
	else if (pattern[0] == 0 && text[0] != 0)
		return (0);
	else
		return (match(text, pattern));
}

void	match_with_directory_compliment(t_dir_match_var *vars, char *pattern)
{
	while (vars->entity)
	{
		if (before_matching(vars->entity->d_name, pattern))
		{
			if (!vars->matched_names)
			{	
				vars->args = malloc(sizeof(t_arguments));
				vars->args_return = vars->args;
				vars->args->previous = 0;
				vars->args->next = 0;
			}
			else
			{
				vars->args->next = malloc(sizeof(t_arguments));
				vars->args->next->previous = vars->args;
				vars->args = vars->args->next;
				vars->args->next = 0;
			}
			vars->matched_names = ft_strdup(vars->entity->d_name);
			vars->args->arg = vars->matched_names;
		}
		vars->entity = readdir(vars->directory);
	}
}

t_arguments	*match_with_directory(char *pattern)
{
	t_dir_match_var	vars;

	vars.matched_names = 0;
	vars.directory = opendir(".");
	vars.entity = readdir(vars.directory);
	match_with_directory_compliment(&vars, pattern);
	closedir(vars.directory);
	if (!vars.matched_names)
		return (0);
	return (vars.args_return);
}
