/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/07 16:34:16 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char** av)
{
	// pthread_t		thread1;
	// pthread_t		thread2;
	// pthread_t		thread3;
	t_meal_table		table;
	// void				*ft_routine(void *tab);
	// int				*tab;

	// struct timeval	start, end;
	// long			secds, usecds;
	// double			elapsed;
	// int				v_ret;

	// check if there is an exact number of arguments
	if (ac < 5)
		return (printf("Wrong number of arguments!\nTry again!\n"), 1);

	// check if all the arguments are numbers
	// how am I going to use that tab ?
	// tab = parsing(ac, av);
	// if (!tab)
	// 	return (1);
	// free(tab);

	// add infos in struct table and free if return value is NULL
	table = (t_meal_table){0} ;
	if (ft_append_infos_table(&table, av) == false)
		return (1);
	// printf("n times : %d\n", table.n_times_to_eat_each);
	table.philosophes = malloc(table.n_philosophes * sizeof(t_philo));
	table.forks = malloc(table.n_philosophes * sizeof(pthread_mutex_t));
	pthread_mutex_init(&table.print_lock, NULL);

	init_philosophes(&table);

	// creates a thread
	// pthread_create(&thread1, NULL, ft_routine, (void *) &table);

	// 1st arg is the id/ptr
	// 2nd arg is attributes (mostly NULL)
	// 3rd arg is the function the thread starts to execute
	// 4th arg is arguments for the routine, can be a structure for multiples args

	// join the threads one by one
	// pthread_join(thread1, NULL);

	// quit a thread (must be inside the pthread_create function passed in argument) || can use a return instead
	// pthread_exit();

	// free structure at the end
	ft_free_struct(&table);
	return (0);
}

// seconds print test
	/*
	gettimeofday(&start, NULL);
	usleep(1000000);
	gettimeofday(&end, NULL);
	secds = end.tv_sec - start.tv_sec;
	usecds = end.tv_usec - start.tv_usec;
	if (usecds < 0)
	{
		secds -= 1;
		usecds +=1000000;
	}
	elapsed = secds * 1000000.0 + usecds;
	printf("Elapsed : %.0f microseconds\n", elapsed);
	*/

void	*ft_routine(void *arg)
{
	t_philo			*philo = (t_philo *)(arg);
	t_meal_table	*table = (t_meal_table *)(arg);

	printf("starting thread...\n");
	philosopher_is_eating(table, philo);
	printf("...ending thread\n");
	printf("\n");
	return (NULL);
}

bool	ft_append_infos_table(t_meal_table *table, char **av)
{
	// Number of Philosophers
	// printf("table->n_philosophes : %d\n", table->n_philosophes);
	table->n_philosophes = ft_atoi(av[1]);
	if (table->n_philosophes == 0)
		return (false);

	// Die limit time in milliseconds
	// printf("table->die_limit : %f\n", table->die_limit);
	table->die_limit = ft_atoi(av[2]);
	if (table->die_limit == 0)
		return (false);

	// Eat limit time
	// printf("table->eat_limit : %f\n", table->eat_limit);
	table->eat_limit = ft_atoi(av[3]);
	if (table->eat_limit == 0)
		return (false);

	// Sleep limit time
	// printf("table->sleep_limit : %f\n", table->sleep_limit);
	table->sleep_limit = ft_atoi(av[4]);
	if (table->sleep_limit == 0)
		return (false);

	// If last parameter, number of times to eat each
	// printf("table->n_times_to_eat_each : %d\n", table->n_times_to_eat_each);
	if (!av[5])
	{
		table->n_times_to_eat_each = -1;
		return (true);
	}

	// If last parameter and it's 0, return false
	if (table->n_times_to_eat_each == 0)
		return (false);
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
		table->philosophes[i].id = i;
		table->philosophes[i].time_to_eat = 0;
		table->philosophes[i].time_to_sleep = 0;
		table->philosophes[i].time_to_die = 0;
		table->philosophes[i].is_dead = false;
		pthread_mutex_init(&table->forks[i], NULL);
	}
	i = -1;
	while (++i < table->n_philosophes)
		pthread_create(&table->philosophes[i].thread, NULL, ft_routine, (void *)&table->philosophes[i]);
	i = -1;
	while (++i < table->n_philosophes)
		pthread_join(table->philosophes[i].thread, NULL);
	i = -1;
	while (++i < table->n_philosophes)
		pthread_mutex_destroy(&table->forks[i]);
	return (0);
}
