/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:51:34 by mel-amma          #+#    #+#             */
/*   Updated: 2022/06/26 11:48:55 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tolower(int a)
{
	if (a >= 65 && a <= 90)
		a += 32;
	return (a);
}

char	*to_lower(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (++i < len)
		str[i] = ft_tolower(str[i]);
	return (str);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
