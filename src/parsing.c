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

int	*parsing(int ac, char **av)
{
	int	i;
	int	*tab;

	i = 1;
	tab = malloc((ac) * sizeof(int));
	if (!tab)
		return (NULL);
	while (av[i])
	{
		if (ft_atoi2(av[i], &tab[i]) == false)
			return (NULL);
		i++;
	}
	return (tab);
}

int	ft_count_av(char **av)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
		i++;
	return (i);
}
