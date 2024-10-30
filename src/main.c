/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:40 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments!\nTry again!\n"), 1);
	if (parsing(ac, av) == false)
		return (1);
	ft_initialisation(&table, av);
	while (1)
	{
		if (end_of_simulation(&table) == 1)
			break ;
		usleep(900);
	}
	i = -1;
	while (++i < table.n_philosophes)
		if (pthread_join(table.philosophes[i].thread, NULL) != 0)
			return (printf("failed to join\n"), 1);
	ft_free_struct(&table);
	return (0);
}

int	end_of_simulation(t_table *table)
{
	if (check_emergency(table) == 0)
		return (1);
	if (check_stomachs_full(table) == 0)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("All philosophers are done eating !\n");
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	usleep(10);
	return (0);
}
