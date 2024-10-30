/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:34:50 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:46 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	parsing(int ac, char **av)
{
	int	i;
	int	j;
	int	*tab;

	i = 1;
	j = 0;
	tab = malloc((ac - 1) * sizeof(int));
	if (!tab)
		return (free(tab), false);
	while (av[i])
	{
		if (ft_atoi2(av[i], &tab[j]) == false)
			return (free(tab), false);
		if (tab[j] <= 0)
			return (free(tab), printf("Error\n"), false);
		i++;
		j++;
	}
	free(tab);
	return (true);
}

int	ft_count_av(char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
		i++;
	return (i);
}
