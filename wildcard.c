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

int no_more_letters(char *pattern)
{
	int i;
	i = 0;
	if(pattern[0] == 0)
	return FALSE;
	while(pattern[i])
	{
		if(pattern[i]!=-1)
		return FALSE;
		i++;
	}
	return TRUE;
}

int match(char *text, char *pattern)
{
	if (!ft_strncmp(text, pattern, PATH_MAX))
		return TRUE;
	else if (pattern[0] == 0 || text[0] == 0)
	{
		if (no_more_letters(pattern))
			return TRUE;
		else
			return FALSE;
	}
	if (pattern[0] == -1)
		return (match(text + 1, pattern) || match(text, pattern + 1));
	else if (pattern[0] == text[0])
		return (match(text + 1, pattern + 1));
	else
		return FALSE;//meanin text and pattern didnt match
}

int before_matching(char *text, char *pattern)
{
	if(text[0] == 0 && pattern[0] != 0)
		return 0;
	else if(pattern[0] == 0 && text[0] != 0)
		return 0;
	else
		return match(text,pattern);
}

t_arguments *match_with_directory(char *pattern)
{
	DIR *directory;
	struct dirent *entity;
	char *matched_names;
	t_arguments *args;
	t_arguments *args_return;
	matched_names = 0;
	directory = opendir(".");
	entity = readdir(directory);
	while(entity)
	{	//printf("check\n");
		if(before_matching(entity->d_name,pattern))
		{
		
			if(!matched_names)
			{	
				args = malloc(sizeof(t_arguments));
				args_return = args;
				args->previous = 0;
				args->next = 0;
			}
			else
			{
				args->next = malloc(sizeof(t_arguments));
				args->next->previous = args;
				args = args->next;
				args->next = 0;
			}
			matched_names = ft_strdup(entity->d_name);// if matched names is still 0 then that means it didnt go in there meanin none has matched
			args->arg = matched_names;
		//	printf("%s\n",matched_names);
		}
		entity = readdir(directory);
	}
	closedir(directory);
	if(!matched_names)
	return 0;
	return(args_return);
}

// t_arguments *get_args_from_matched(char *matched_names)
// {
// 	t_arguments *args;
// 	t_arguments *args_return;
// 	char **words;
// 	int i;
// 	int  j;
// 	i = 0;
// 	j = 0;
// 	words = ft_split_whitespaces(matched_names);
// 	while(words[i])
// 		i++;
// 	args = malloc(sizeof(t_arguments));
// 	args_return = args;
// 	args->previous = 0;
	
// 	while(args)
// 	{
// 		args->arg = words[j];
// 		j++;
		
// 		args->next = 0;
// 		if(j < i)
// 		{
// 			args->next = malloc(sizeof(t_arguments));
// 			args->next->previous = args;
// 		}
// 		args = args->next;
// 	}
// 	free(words);
// 	free(matched_names);
// 	return args_return;
// }
// int main(int argc, char **argv)
// {
// // 	char *text;
// 	char *pattern;
// // 	int matched;
// 	pattern = argv[1];
// // 	text = argv[2];
// // 	if(!text || !pattern)
// // 	{
// // 		printf("null argument\n");
// // 		return 1;
// // 	}
// // 	else
// // 		matched = before_matching(text,pattern);
// // //	printf("%s\n%s\n",pattern,text);

// // 	printf("%d \n",matched);
// t_arguments *args = 0;
// char *pp = match_with_directory(pattern);
// printf("%s___\n",pp);
// if(pp)
// {
// args  = get_args_from_matched(pp);
// //if(args)
// //printf("lol\n");
// pp = 0;

// }
// while(args)
// {
// 	printf(" %p____%s____%p\n",args->previous,args->arg,args->next);
// 	//printf("%s\n",args->arg);
// 	if(args->next == 0)
// 	break;
// 	args = args -> next;
// }
// // fflush(stdout);
// // while(args)
// // free(args->arg)
// ///printf("matched names : %s\n",pp);
// //free(pp);
// system("leaks a.out");
// return 0;
// }
// int main(int argc, char **argv)
// {
// 	t_arguments *args = match_with_directory(argv[1]);

// 	if(!args)
// 	printf("none\n");
// 	while(args)
// 	{
// 		printf("%p__%s___%p\n",args->previous,args->arg,args->next);
// 		args = args->next;
// 	}
// }