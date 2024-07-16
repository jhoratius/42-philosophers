/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:34:50 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/07/16 17:26:24 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	*parsing(char **av)
{
	int	i;
	int	tab[ft_count_av(av)];

	i = 1;
	while (av[i] != NULL)
	{
		if(ft_atoi2(av[i], tab[i]) == false)
			return (NULL);
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
