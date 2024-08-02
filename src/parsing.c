/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:34:50 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/02 18:34:30 by jhoratiu         ###   ########.fr       */
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
		printf("av[i] : %s\n", av[i]);
		if(ft_atoi2(av[i], &tab[i]) == false)
			return (NULL);
		i++;
	}
	// check first argument (av[1]) so that it's a number
	// [number of philosophers]

	// check the second argument (av[2]), so that it's a number in milliseconds
	// [time to die]

	// check the third argument (av[3]), so that it's a number in milliseconds
	// [time to eat]

	// check the fourth argument (av[4]), so that it's a number in milliseconds
	// [time to sleep]

	// check the fifth and last argument (av[5]), so that it's a number
	// [number of time each philosopher must eat]
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
