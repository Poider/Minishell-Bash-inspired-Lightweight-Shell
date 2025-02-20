/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:51:34 by mel-amma          #+#    #+#             */
/*   Updated: 2022/03/22 12:46:54 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	j = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (j < len && s[start])
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	if (str == 0)
		return (0);
	len = ft_strlen((char *)s1);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

//alnum+underscore
int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else if (c == 95)
		return (1);
	return (0);
}

int	numbcount(int n)
{
	long int	a;
	int			i;

	a = n;
	if (n < 0)
	{
		a = n;
		a = -a;
	}
	i = 0;
	while (a >= 10)
	{
		a = a / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		numblen;
	int		i;
	long	work;

	i = 0;
	work = (long)n;
	numblen = numbcount(n);
	if (n < 0)
		numblen++;
	res = (char *)malloc(sizeof(char) * (numblen + 1));
	if (res == 0)
		return (0);
	if (n < 0)
	{
		res[i++] = '-';
		work = -work;
	}
	res[numblen] = '\0';
	while (i < numblen)
	{
		res[numblen-- - 1] = work % 10 + 48;
		work = work / 10;
	}
	return (res);
}
