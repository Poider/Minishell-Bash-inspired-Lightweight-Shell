/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:27:51 by mel-amma          #+#    #+#             */
/*   Updated: 2022/10/21 14:38:52 by mel-amma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	long_numb(char *s, unsigned long long sum, int i, \
		unsigned long long numb)
{
	if (sum > numb && i == 1)
	{
		printf("exit\n");
		write (2, "bash tsetta: exit: ", 19);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
		g_v_lines->exit_status = 255;
		exit(255);
	}
	else if (sum > (numb + 1) && i == -1)
	{
		printf("exit\n");
		write (2, "bash tsetta: exit: ", 19);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
		g_v_lines->exit_status = 255;
		exit(255);
	}
}

int	exit_atoi(const char *s)
{
	long long			i;
	int					sign;
	unsigned long long	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (s[i] == ' ' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r' || s[i] == '\n')
		i++;
	if (s[i] == '+' && s[i + 1] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	while (s[i] != '\0' && s[i] >= 48 && s[i] <= 57)
	{
		sum = sum * 10 + (s[i++] - '0');
		long_numb((char *)s, sum, sign, 9223372036854775807);
	}
	return (sign * sum);
}
