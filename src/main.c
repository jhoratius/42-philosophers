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

	// add infos in struct table and free if return value is NULL
	table = (t_meal_table){0} ;
	if (ft_append_infos_table(&table, av) == false)
		return (1);
	// printf("n times : %d\n", table.n_times_to_eat_each);
	table.philosophes = malloc(table.n_philosophes * sizeof(t_philo));
	if (!table.philosophes)
		return (1);
	// printf("n philo : %d\n", table.n_philosophes);
	table.forks = malloc(table.n_philosophes * sizeof(pthread_mutex_t));
	if (!table.forks)
		return (free(table.philosophes), 1);
	init_philosophes(&table);
	pthread_mutex_init(&table.print_lock, NULL);
	// free structure at the end
	ft_free_struct(&table);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;
	t_meal_table	*table;
	int				i;

	philo = (t_philo *)(arg);
	table = philo->table;
	if (philo->id % 2 == 1)
		sleep(1);
	i = 0;
	while (1)
	{
		if (philosopher_is_eating(table, philo) == 1)
			return (NULL);
		if (philosopher_is_sleeping(table, philo) == 1)
			return (NULL);
		if (philosopher_is_thinking(table, philo) == 1)
			return (NULL);
		if (table->n_times_to_eat_each != -1 && i >= table->n_times_to_eat_each)
		{
			printf("Philosopher %d has the belly full\n", philo->id);
			break ;
		}
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
	// printf("table->n_philosophes : %d\n", table->n_philosophes);

	// Die limit time in milliseconds
	table->die_limit = ft_atoi(av[2]);
	if (table->die_limit == 0)
		return (printf("no die limit\n"), false);
	// printf("table->die_limit : %f\n", table->die_limit);

	// Eat limit time
	table->eat_limit = ft_atoi(av[3]);
	if (table->eat_limit == 0)
		return (printf("no eat limit\n"), false);
	// printf("table->eat_limit : %f\n", table->eat_limit);

	// Sleep limit time
	// printf("table->sleep_limit : %f\n", table->sleep_limit);
	table->sleep_limit = ft_atoi(av[4]);
	if (table->sleep_limit == 0)
		return (printf("no sleep limit\n"), false);

	// If last parameter, number of times to eat each
	// printf("table->n_times_to_eat_each : %d\n", table->n_times_to_eat_each);
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
		pthread_mutex_init(&table->forks[i], NULL);
	}

	pthread_mutex_init(&table->print_lock, NULL);
	i = -1;
	table->start_time = get_time();
	// printf("table start time: %zu\n", table->start_time);
	while (++i < table->n_philosophes)
	{
		// fprintf(stderr, "i:%d\n", i);
		if(pthread_create(&table->philosophes[i].thread, NULL, ft_routine, (void *)&table->philosophes[i]) != 0)
			printf("failed to create\n");
	}
	i = -1;
	while (++i < table->n_philosophes)
		if (pthread_join(table->philosophes[i].thread, NULL) != 0)
			printf("failed to join\n");
	i = -1;
	while (++i < table->n_philosophes)
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			printf("failed to destroy\n");
	free(table->philosophes);
    free(table->forks);
	return (0);
}
