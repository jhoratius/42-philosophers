/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/27 19:01:54 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

	// check if all the arguments are numbers
	// how am I going to use that tab ?
	// tab = parsing(ac, av);
	// if (!tab)
	// 	return (1);
	// free(tab);

int	main(int ac, char** av)
{
	t_meal_table		table;

	if (ac < 5)
		return (printf("Wrong number of arguments!\nTry again!\n"), 1);
	ft_initialisation(&table, av);
	while (1)
	{
		if (end_of_simulation(&table) == 1)
			break ;
	}
	ft_free_struct(&table);
	return (0);
}

int	end_of_simulation(t_meal_table *table)
{
	if (check_philo_died(table) == 0)
	{
		pthread_mutex_lock(&table->someone_died);
		table->emergency_call = true;
		pthread_mutex_unlock(&table->someone_died);
		return (1);
	}
	pthread_mutex_lock(&table->someone_died);
	if (table->stomachs_full == true)
	{
		printf("All philosophers are done eating !\n");
		pthread_mutex_unlock(&table->someone_died);
		return (1);
	}
	pthread_mutex_unlock(&table->someone_died);
	return (0);
}
