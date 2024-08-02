/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:57:48 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/02 18:24:45 by jhoratiu         ###   ########.fr       */
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
	long	signe;
	long	j;

	i = 0;
	signe = 1;
	j = 0;
	printf("1");
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	signe = ft_check_sign(nptr[i], &i);
	printf("2");
	if (signe != 1 && signe != -1)
		return (false);
	printf("3");
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (((signe > 0 && (j * 10 + nptr[i] - 48) > INT_MAX))
			|| ((signe < 0 && (j * 10 + nptr[i] - 48) * signe < INT_MIN)))
			return (write(2, "Error\n", 6), false);
		j = j * 10 + nptr[i] - 48;
		i += 1;
	}
	printf("4\n");
	if (nptr[i] && (!(nptr[i] == '\0')))
		return (write(2, "Error\n", 6), false);
	*n = j * signe;
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
