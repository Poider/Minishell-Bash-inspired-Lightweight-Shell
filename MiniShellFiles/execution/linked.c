/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:42:28 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:46:21 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_list	*ft_lstnew(char *first, char *second)
{
	t_list	*new;

	new = malloc (sizeof(t_list));
	if (!new)
		return (0);
	new->next = NULL;
	new->key = first;
	new->value = second;
	return (new);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

void	ft_lstadd_back1(t_list **head, t_list *new)
{
	t_list	*tmp;

	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_list	*del_node(t_list *list_head, t_list *node_2_delete)
{
	t_list	*head;
	t_list	*next;

	head = list_head;
	next = node_2_delete->next;
	if (head == node_2_delete)
	{
		g_v_lines->env_vars_head = node_2_delete->next;
	}
	else
	{
		while (head->next != node_2_delete)
		{
			head = head->next;
		}
		head->next = next;
	}
	free(node_2_delete->key);
	free(node_2_delete->value);
	free(node_2_delete);
	return (next);
}

int	ft_lstsize(t_arguments *lst)
{
	int			i;
	t_arguments	*itering;

	itering = lst;
	i = 0;
	while (itering)
	{
		itering = itering->next;
		i++;
	}
	return (i);
}
