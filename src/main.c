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

	table = (t_meal_table){0} ;
	if (ft_append_infos_table(&table, av) == false)
		return (1);
	table.philosophes = malloc(table.n_philosophes * sizeof(t_philo));
	if (!table.philosophes)
		return (1);
	table.forks = malloc(table.n_philosophes * sizeof(pthread_mutex_t));
	if (!table.forks)
		return (free(table.philosophes), 1);
	init_philosophes(&table);
	
	if (all_philo_died(&table) == 1)
		printf("All philosophers are done eating !\n");
	ft_free_struct(&table);
	return (0);
}

int	all_philo_died(t_meal_table *table)
{
	(void)table;
	int	i;

	i = 0;
	while (i < table->n_philosophes)
	{
		if (table->philosophes[i].is_dead == true)
			return (0);
		i++;
	}
	return (1);
}

int	init_philosophes(t_meal_table *table)
{
	int	i;

	if (!table)
		return (1);
	i = -1;
	while(++i < table->n_philosophes)
	{
		table->philosophes[i].id = i + 1;
		table->philosophes[i].is_dead = false;
		table->philosophes[i].nb_eat_times = 0;
		table->philosophes[i].table = table;
		table->philosophes[i].time_to_eat = 0;
		pthread_mutex_init(&table->forks[i], NULL);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	table->start_time = get_time();
	i = -1;
	while (++i < table->n_philosophes)
	{
		if(pthread_create(&table->philosophes[i].thread, NULL, 
			(void *)ft_routine, &table->philosophes[i]) != 0)
			return (printf("failed to create\n"), 1);
	}
	i = -1;
	while (++i < table->n_philosophes)
		if (pthread_join(table->philosophes[i].thread, NULL) != 0)
			return (printf("failed to join\n"), 1);
	free(table->philosophes);
	free(table->forks);
	return (0);
}

void	*ft_routine(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->id % 2 == 1)
		usleep(philo->time_to_eat / 2);
	while (1)
	{
		if (philo->table->n_times_to_eat_each != -1
			&& i > (philo->table->n_times_to_eat_each - 1))
			break ;
		if (philosopher_is_eating(philo->table, philo) == 1)
			return (NULL);
		if (philosopher_is_sleeping(philo->table, philo) == 1)
			return (NULL);
		if (philosopher_is_thinking(philo->table, philo) == 1)
			return (NULL);
		i++;
	}
	return (NULL);
}


bool	ft_append_infos_table(t_meal_table *table, char **av)
{
	// Number of Philosophers
	table->n_philosophes = ft_atoi(av[1]);
	if (table->n_philosophes == 0)
		return (printf("no philosophers\n"), false);
	printf("table->n_philosophes : %d\n", table->n_philosophes);

	// Die limit time in milliseconds
	table->die_limit = ft_atoi(av[2]);
	if (table->die_limit == 0)
		return (printf("no die limit\n"), false);
	printf("table->die_limit : %ld\n", table->die_limit);

	// Eat limit time
	table->eat_limit = ft_atoi(av[3]);
	if (table->eat_limit == 0)
		return (printf("no eat limit\n"), false);
	printf("table->eat_limit : %ld\n", table->eat_limit);

	// Sleep limit time
	table->sleep_limit = ft_atoi(av[4]);
	if (table->sleep_limit == 0)
		return (printf("no sleep limit\n"), false);
	printf("table->sleep_limit : %ld\n", table->sleep_limit);

	// If last parameter, number of times to eat each
	printf("table->n_times_to_eat_each : %d\n", table->n_times_to_eat_each);
	if (!av[5])
	{
		table->n_times_to_eat_each = -1;
		return (true);
	}

	// If last parameter and it's 0, return false
	table->n_times_to_eat_each = ft_atoi(av[5]);
	if (table->n_times_to_eat_each == 0)
		return (printf("no n times to eat each\n"), false);
	return (true);
}
