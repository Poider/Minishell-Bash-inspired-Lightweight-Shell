/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:11:19 by maamer            #+#    #+#             */
/*   Updated: 2022/10/21 12:46:14 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	result;

	n = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
			i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * n);
}

char	*ft_strchr(const char *s, int c)
{
	char	*k;
	int		i;

	i = 0;
	k = (char *)s;
	c = (char)c;
	if (c == '\0')
		return (k + ft_strlen(k));
	while (k[i] != '\0')
	{
		if (k[i] == c)
			return (k + i);
		i++;
	}
	return (NULL);
}
