/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:57:48 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/04 12:25:21 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	n;

	i = 0;
	signe = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		n = n * 10 + nptr[i] - 48;
		i++;
	}
	return (n * signe);
}

bool	ft_atoi2(const char *nptr, int *n)
{
	int		i;
	long	sign;
	long	j;

	i = 0;
	sign = 1;
	j = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	sign = ft_check_sign(nptr[i], &i);
	if (sign != 1 && sign != -1)
		return (false);
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (((sign > 0 && (j * 10 + nptr[i] - 48) > INT_MAX))
			|| ((sign < 0 && (j * 10 + nptr[i] - 48) * sign < INT_MIN)))
			return (write(2, "Error : Argument overflow\n", 27), false);
		j = j * 10 + nptr[i] - 48;
		i += 1;
	}
	if (nptr[i] && (!(nptr[i] == '\0')))
		return (write(2, "Error\n", 6), false);
	*n = j * sign;
	return (true);
}

long	ft_check_sign(char c, int *i)
{
	if (c == '-')
	{
		(*i)++;
		return (-1);
	}
	else if (c == '+')
	{
		(*i)++;
		return (1);
	}
	else if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
