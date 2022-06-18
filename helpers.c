/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:43:07 by mel-amma          #+#    #+#             */
/*   Updated: 2022/02/22 14:45:05 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifset(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		slen;
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (0);
	slen = ft_strlen((char *)s1);
	while (ifset(s1[i], set))
		i++;
	while (i < slen && ifset(s1[slen - 1], set))
		slen--;
	res = (char *)malloc(sizeof(char) * (slen - i + 1));
	if (res == 0)
		return (0);
	while (i < slen)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2 && n != 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && i < n - 1)
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if(!str)
	return 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lentotal;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = "";
	if(!s2)
		s2 = "";
	lentotal = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (lentotal + 1));
	if (str == 0)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char *to_lower(char *str)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(str);
	while(++i < len)
		str[i] = ft_tolower(str[i]);
	return str;
}